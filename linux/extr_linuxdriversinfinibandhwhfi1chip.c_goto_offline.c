#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  int u32 ;
struct TYPE_2__ {scalar_t__ reset_needed; scalar_t__ limiting_active; } ;
struct hfi1_pportdata {int host_link_state; scalar_t__ offline_disabled_reason; scalar_t__ port_type; scalar_t__ current_egress_rate; scalar_t__ link_width_downgrade_rx_active; scalar_t__ link_width_downgrade_tx_active; scalar_t__ link_width_active; TYPE_1__ qsfp_info; struct hfi1_devdata* dd; } ;
struct hfi1_devdata {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DC_LCB_ERR_EN ; 
 int EINVAL ; 
 int HCMD_SUCCESS ; 
 scalar_t__ HFI1_ODR_MASK (int /*<<< orphan*/ ) ; 
 void* HLS_DN_OFFLINE ; 
 int HLS_DN_POLL ; 
 int HLS_GOING_OFFLINE ; 
 int HLS_GOING_UP ; 
 int HLS_LINK_COOLDOWN ; 
 int HLS_UP ; 
 int HLS_VERIFY_CAP ; 
 int /*<<< orphan*/  IB_PORT_DOWN ; 
 int /*<<< orphan*/  OPA_LINKDOWN_REASON_NONE ; 
 int /*<<< orphan*/  OPA_LINKDOWN_REASON_TRANSIENT ; 
 int PLS_OFFLINE ; 
 int PLS_OFFLINE_QUIET ; 
 scalar_t__ PORT_TYPE_QSFP ; 
 int /*<<< orphan*/  QSFP_WAIT ; 
 int acquire_chip_resource (struct hfi1_devdata*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  check_lni_states (struct hfi1_pportdata*) ; 
 int /*<<< orphan*/  dd_dev_err (struct hfi1_devdata*,char*,...) ; 
 int /*<<< orphan*/  force_logical_link_state_down (struct hfi1_pportdata*) ; 
 int /*<<< orphan*/  handle_linkup_change (struct hfi1_devdata*,int /*<<< orphan*/ ) ; 
 scalar_t__ qsfp_mod_present (struct hfi1_pportdata*) ; 
 int /*<<< orphan*/  qsfp_resource (struct hfi1_devdata*) ; 
 int /*<<< orphan*/  release_chip_resource (struct hfi1_devdata*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_host_lcb_access (struct hfi1_devdata*) ; 
 int set_physical_link_state (struct hfi1_devdata*,int) ; 
 int /*<<< orphan*/  set_qsfp_tx (struct hfi1_pportdata*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  update_lcb_cache (struct hfi1_devdata*) ; 
 int /*<<< orphan*/  update_statusp (struct hfi1_pportdata*,int /*<<< orphan*/ ) ; 
 int wait_fm_ready (struct hfi1_devdata*,int) ; 
 int wait_logical_linkstate (struct hfi1_pportdata*,int /*<<< orphan*/ ,int) ; 
 int wait_phys_link_offline_substates (struct hfi1_pportdata*,int) ; 
 int wait_physical_linkstate (struct hfi1_pportdata*,int,int) ; 
 int /*<<< orphan*/  write_csr (struct hfi1_devdata*,int /*<<< orphan*/ ,unsigned long long) ; 

__attribute__((used)) static int goto_offline(struct hfi1_pportdata *ppd, u8 rem_reason)
{
	struct hfi1_devdata *dd = ppd->dd;
	u32 previous_state;
	int offline_state_ret;
	int ret;

	update_lcb_cache(dd);

	previous_state = ppd->host_link_state;
	ppd->host_link_state = HLS_GOING_OFFLINE;

	/* start offline transition */
	ret = set_physical_link_state(dd, (rem_reason << 8) | PLS_OFFLINE);

	if (ret != HCMD_SUCCESS) {
		dd_dev_err(dd,
			   "Failed to transition to Offline link state, return %d\n",
			   ret);
		return -EINVAL;
	}
	if (ppd->offline_disabled_reason ==
			HFI1_ODR_MASK(OPA_LINKDOWN_REASON_NONE))
		ppd->offline_disabled_reason =
		HFI1_ODR_MASK(OPA_LINKDOWN_REASON_TRANSIENT);

	offline_state_ret = wait_phys_link_offline_substates(ppd, 10000);
	if (offline_state_ret < 0)
		return offline_state_ret;

	/* Disabling AOC transmitters */
	if (ppd->port_type == PORT_TYPE_QSFP &&
	    ppd->qsfp_info.limiting_active &&
	    qsfp_mod_present(ppd)) {
		int ret;

		ret = acquire_chip_resource(dd, qsfp_resource(dd), QSFP_WAIT);
		if (ret == 0) {
			set_qsfp_tx(ppd, 0);
			release_chip_resource(dd, qsfp_resource(dd));
		} else {
			/* not fatal, but should warn */
			dd_dev_err(dd,
				   "Unable to acquire lock to turn off QSFP TX\n");
		}
	}

	/*
	 * Wait for the offline.Quiet transition if it hasn't happened yet. It
	 * can take a while for the link to go down.
	 */
	if (offline_state_ret != PLS_OFFLINE_QUIET) {
		ret = wait_physical_linkstate(ppd, PLS_OFFLINE, 30000);
		if (ret < 0)
			return ret;
	}

	/*
	 * Now in charge of LCB - must be after the physical state is
	 * offline.quiet and before host_link_state is changed.
	 */
	set_host_lcb_access(dd);
	write_csr(dd, DC_LCB_ERR_EN, ~0ull); /* watch LCB errors */

	/* make sure the logical state is also down */
	ret = wait_logical_linkstate(ppd, IB_PORT_DOWN, 1000);
	if (ret)
		force_logical_link_state_down(ppd);

	ppd->host_link_state = HLS_LINK_COOLDOWN; /* LCB access allowed */
	update_statusp(ppd, IB_PORT_DOWN);

	/*
	 * The LNI has a mandatory wait time after the physical state
	 * moves to Offline.Quiet.  The wait time may be different
	 * depending on how the link went down.  The 8051 firmware
	 * will observe the needed wait time and only move to ready
	 * when that is completed.  The largest of the quiet timeouts
	 * is 6s, so wait that long and then at least 0.5s more for
	 * other transitions, and another 0.5s for a buffer.
	 */
	ret = wait_fm_ready(dd, 7000);
	if (ret) {
		dd_dev_err(dd,
			   "After going offline, timed out waiting for the 8051 to become ready to accept host requests\n");
		/* state is really offline, so make it so */
		ppd->host_link_state = HLS_DN_OFFLINE;
		return ret;
	}

	/*
	 * The state is now offline and the 8051 is ready to accept host
	 * requests.
	 *	- change our state
	 *	- notify others if we were previously in a linkup state
	 */
	ppd->host_link_state = HLS_DN_OFFLINE;
	if (previous_state & HLS_UP) {
		/* went down while link was up */
		handle_linkup_change(dd, 0);
	} else if (previous_state
			& (HLS_DN_POLL | HLS_VERIFY_CAP | HLS_GOING_UP)) {
		/* went down while attempting link up */
		check_lni_states(ppd);

		/* The QSFP doesn't need to be reset on LNI failure */
		ppd->qsfp_info.reset_needed = 0;
	}

	/* the active link width (downgrade) is 0 on link down */
	ppd->link_width_active = 0;
	ppd->link_width_downgrade_tx_active = 0;
	ppd->link_width_downgrade_rx_active = 0;
	ppd->current_egress_rate = 0;
	return 0;
}