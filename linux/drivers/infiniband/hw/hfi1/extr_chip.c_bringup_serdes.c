#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  scalar_t__ u64 ;
struct hfi1_pportdata {scalar_t__ port_type; int /*<<< orphan*/  linkinit_reason; scalar_t__* guids; scalar_t__ port; struct hfi1_devdata* dd; } ;
struct hfi1_devdata {scalar_t__ base_guid; } ;

/* Variables and functions */
 int /*<<< orphan*/  EXTENDED_PSN ; 
 scalar_t__ HFI1_CAP_IS_KSET (int /*<<< orphan*/ ) ; 
 size_t HFI1_PORT_GUID_INDEX ; 
 int /*<<< orphan*/  OPA_LINKINIT_REASON_LINKUP ; 
 scalar_t__ PORT_TYPE_QSFP ; 
 int /*<<< orphan*/  RCV_CTRL_RCV_EXTENDED_PSN_ENABLE_SMASK ; 
 int /*<<< orphan*/  add_rcvctrl (struct hfi1_devdata*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_port_type (struct hfi1_pportdata*) ; 
 int /*<<< orphan*/  init_lcb (struct hfi1_devdata*) ; 
 int init_loopback (struct hfi1_devdata*) ; 
 scalar_t__ loopback ; 
 int /*<<< orphan*/  set_qsfp_int_n (struct hfi1_pportdata*,int) ; 
 int /*<<< orphan*/  try_start_link (struct hfi1_pportdata*) ; 
 int /*<<< orphan*/  wait_for_qsfp_init (struct hfi1_pportdata*) ; 

int bringup_serdes(struct hfi1_pportdata *ppd)
{
	struct hfi1_devdata *dd = ppd->dd;
	u64 guid;
	int ret;

	if (HFI1_CAP_IS_KSET(EXTENDED_PSN))
		add_rcvctrl(dd, RCV_CTRL_RCV_EXTENDED_PSN_ENABLE_SMASK);

	guid = ppd->guids[HFI1_PORT_GUID_INDEX];
	if (!guid) {
		if (dd->base_guid)
			guid = dd->base_guid + ppd->port - 1;
		ppd->guids[HFI1_PORT_GUID_INDEX] = guid;
	}

	/* Set linkinit_reason on power up per OPA spec */
	ppd->linkinit_reason = OPA_LINKINIT_REASON_LINKUP;

	/* one-time init of the LCB */
	init_lcb(dd);

	if (loopback) {
		ret = init_loopback(dd);
		if (ret < 0)
			return ret;
	}

	get_port_type(ppd);
	if (ppd->port_type == PORT_TYPE_QSFP) {
		set_qsfp_int_n(ppd, 0);
		wait_for_qsfp_init(ppd);
		set_qsfp_int_n(ppd, 1);
	}

	try_start_link(ppd);
	return 0;
}