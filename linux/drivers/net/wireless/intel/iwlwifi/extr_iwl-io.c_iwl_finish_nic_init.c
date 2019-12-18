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
struct iwl_trans {int dummy; } ;
struct iwl_cfg_trans_params {scalar_t__ device_family; scalar_t__ bisr_workaround; TYPE_1__* csr; } ;
struct TYPE_2__ {int /*<<< orphan*/  flag_mac_clock_ready; int /*<<< orphan*/  flag_init_done; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CSR_GP_CNTRL ; 
 int /*<<< orphan*/  IWL_DEBUG_INFO (struct iwl_trans*,char*) ; 
 scalar_t__ IWL_DEVICE_FAMILY_8000 ; 
 int iwl_poll_bit (struct iwl_trans*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  iwl_set_bit (struct iwl_trans*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mdelay (int) ; 
 int /*<<< orphan*/  udelay (int) ; 

int iwl_finish_nic_init(struct iwl_trans *trans,
			const struct iwl_cfg_trans_params *cfg_trans)
{
	int err;

	if (cfg_trans->bisr_workaround) {
		/* ensure the TOP FSM isn't still in previous reset */
		mdelay(2);
	}

	/*
	 * Set "initialization complete" bit to move adapter from
	 * D0U* --> D0A* (powered-up active) state.
	 */
	iwl_set_bit(trans, CSR_GP_CNTRL,
		    BIT(cfg_trans->csr->flag_init_done));

	if (cfg_trans->device_family == IWL_DEVICE_FAMILY_8000)
		udelay(2);

	/*
	 * Wait for clock stabilization; once stabilized, access to
	 * device-internal resources is supported, e.g. iwl_write_prph()
	 * and accesses to uCode SRAM.
	 */
	err = iwl_poll_bit(trans, CSR_GP_CNTRL,
			   BIT(cfg_trans->csr->flag_mac_clock_ready),
			   BIT(cfg_trans->csr->flag_mac_clock_ready),
			   25000);
	if (err < 0)
		IWL_DEBUG_INFO(trans, "Failed to wake NIC\n");

	if (cfg_trans->bisr_workaround) {
		/* ensure BISR shift has finished */
		udelay(200);
	}

	return err < 0 ? err : 0;
}