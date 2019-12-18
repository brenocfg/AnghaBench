#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct iwl_trans {int /*<<< orphan*/  status; TYPE_2__* cfg; TYPE_3__* trans_cfg; } ;
struct TYPE_6__ {scalar_t__ device_family; TYPE_1__* base_params; } ;
struct TYPE_5__ {int /*<<< orphan*/  apmg_not_supported; scalar_t__ host_interrupt_operation_mode; } ;
struct TYPE_4__ {scalar_t__ pll_cfg; } ;

/* Variables and functions */
 int /*<<< orphan*/  APMG_CLK_EN_REG ; 
 int /*<<< orphan*/  APMG_CLK_VAL_DMA_CLK_RQT ; 
 int /*<<< orphan*/  APMG_PCIDEV_STT_REG ; 
 int /*<<< orphan*/  APMG_PCIDEV_STT_VAL_L1_ACT_DIS ; 
 int /*<<< orphan*/  APMG_RTC_INT_STT_REG ; 
 int /*<<< orphan*/  APMG_RTC_INT_STT_RFKILL ; 
 int /*<<< orphan*/  CSR50_ANA_PLL_CFG_VAL ; 
 int /*<<< orphan*/  CSR_ANA_PLL_CFG ; 
 int /*<<< orphan*/  CSR_DBG_HPET_MEM_REG ; 
 int /*<<< orphan*/  CSR_DBG_HPET_MEM_REG_VAL ; 
 int /*<<< orphan*/  CSR_GIO_CHICKEN_BITS ; 
 int /*<<< orphan*/  CSR_GIO_CHICKEN_BITS_REG_BIT_DIS_L0S_EXIT_TIMER ; 
 int /*<<< orphan*/  CSR_GIO_CHICKEN_BITS_REG_BIT_L1A_NO_L0S_RX ; 
 int /*<<< orphan*/  CSR_HW_IF_CONFIG_REG ; 
 int /*<<< orphan*/  CSR_HW_IF_CONFIG_REG_BIT_HAP_WAKE_L1A ; 
 int /*<<< orphan*/  IWL_DEBUG_INFO (struct iwl_trans*,char*) ; 
 scalar_t__ IWL_DEVICE_FAMILY_8000 ; 
 int /*<<< orphan*/  OSC_CLK ; 
 int /*<<< orphan*/  OSC_CLK_FORCE_CONTROL ; 
 int /*<<< orphan*/  STATUS_DEVICE_ENABLED ; 
 int iwl_finish_nic_init (struct iwl_trans*,TYPE_3__*) ; 
 int /*<<< orphan*/  iwl_pcie_apm_config (struct iwl_trans*) ; 
 int /*<<< orphan*/  iwl_read_prph (struct iwl_trans*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iwl_set_bit (struct iwl_trans*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iwl_set_bits_prph (struct iwl_trans*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iwl_write_prph (struct iwl_trans*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int iwl_pcie_apm_init(struct iwl_trans *trans)
{
	int ret;

	IWL_DEBUG_INFO(trans, "Init card's basic functions\n");

	/*
	 * Use "set_bit" below rather than "write", to preserve any hardware
	 * bits already set by default after reset.
	 */

	/* Disable L0S exit timer (platform NMI Work/Around) */
	if (trans->trans_cfg->device_family < IWL_DEVICE_FAMILY_8000)
		iwl_set_bit(trans, CSR_GIO_CHICKEN_BITS,
			    CSR_GIO_CHICKEN_BITS_REG_BIT_DIS_L0S_EXIT_TIMER);

	/*
	 * Disable L0s without affecting L1;
	 *  don't wait for ICH L0s (ICH bug W/A)
	 */
	iwl_set_bit(trans, CSR_GIO_CHICKEN_BITS,
		    CSR_GIO_CHICKEN_BITS_REG_BIT_L1A_NO_L0S_RX);

	/* Set FH wait threshold to maximum (HW error during stress W/A) */
	iwl_set_bit(trans, CSR_DBG_HPET_MEM_REG, CSR_DBG_HPET_MEM_REG_VAL);

	/*
	 * Enable HAP INTA (interrupt from management bus) to
	 * wake device's PCI Express link L1a -> L0s
	 */
	iwl_set_bit(trans, CSR_HW_IF_CONFIG_REG,
		    CSR_HW_IF_CONFIG_REG_BIT_HAP_WAKE_L1A);

	iwl_pcie_apm_config(trans);

	/* Configure analog phase-lock-loop before activating to D0A */
	if (trans->trans_cfg->base_params->pll_cfg)
		iwl_set_bit(trans, CSR_ANA_PLL_CFG, CSR50_ANA_PLL_CFG_VAL);

	ret = iwl_finish_nic_init(trans, trans->trans_cfg);
	if (ret)
		return ret;

	if (trans->cfg->host_interrupt_operation_mode) {
		/*
		 * This is a bit of an abuse - This is needed for 7260 / 3160
		 * only check host_interrupt_operation_mode even if this is
		 * not related to host_interrupt_operation_mode.
		 *
		 * Enable the oscillator to count wake up time for L1 exit. This
		 * consumes slightly more power (100uA) - but allows to be sure
		 * that we wake up from L1 on time.
		 *
		 * This looks weird: read twice the same register, discard the
		 * value, set a bit, and yet again, read that same register
		 * just to discard the value. But that's the way the hardware
		 * seems to like it.
		 */
		iwl_read_prph(trans, OSC_CLK);
		iwl_read_prph(trans, OSC_CLK);
		iwl_set_bits_prph(trans, OSC_CLK, OSC_CLK_FORCE_CONTROL);
		iwl_read_prph(trans, OSC_CLK);
		iwl_read_prph(trans, OSC_CLK);
	}

	/*
	 * Enable DMA clock and wait for it to stabilize.
	 *
	 * Write to "CLK_EN_REG"; "1" bits enable clocks, while "0"
	 * bits do not disable clocks.  This preserves any hardware
	 * bits already set by default in "CLK_CTRL_REG" after reset.
	 */
	if (!trans->cfg->apmg_not_supported) {
		iwl_write_prph(trans, APMG_CLK_EN_REG,
			       APMG_CLK_VAL_DMA_CLK_RQT);
		udelay(20);

		/* Disable L1-Active */
		iwl_set_bits_prph(trans, APMG_PCIDEV_STT_REG,
				  APMG_PCIDEV_STT_VAL_L1_ACT_DIS);

		/* Clear the interrupt in APMG if the NIC is in RFKILL */
		iwl_write_prph(trans, APMG_RTC_INT_STT_REG,
			       APMG_RTC_INT_STT_RFKILL);
	}

	set_bit(STATUS_DEVICE_ENABLED, &trans->status);

	return 0;
}