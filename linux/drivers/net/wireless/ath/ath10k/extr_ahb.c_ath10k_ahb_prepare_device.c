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
typedef  int /*<<< orphan*/  u32 ;
struct ath10k {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATH10K_AHB_GCC_FEPLL_PLL_DIV ; 
 int /*<<< orphan*/  ATH10K_AHB_WIFI_SCRATCH_5_REG ; 
 int /*<<< orphan*/  FW_INDICATOR_ADDRESS ; 
 int /*<<< orphan*/  FW_IND_HOST_READY ; 
 int /*<<< orphan*/  ath10k_ahb_clock_disable (struct ath10k*) ; 
 int ath10k_ahb_clock_enable (struct ath10k*) ; 
 int /*<<< orphan*/  ath10k_ahb_gcc_read32 (struct ath10k*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ath10k_ahb_halt_chip (struct ath10k*) ; 
 int /*<<< orphan*/  ath10k_ahb_irq_disable (struct ath10k*) ; 
 int ath10k_ahb_release_reset (struct ath10k*) ; 
 int /*<<< orphan*/  ath10k_ahb_write32 (struct ath10k*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ath10k_err (struct ath10k*,char*) ; 
 int ath10k_pci_wait_for_target_init (struct ath10k*) ; 

__attribute__((used)) static int ath10k_ahb_prepare_device(struct ath10k *ar)
{
	u32 val;
	int ret;

	ret = ath10k_ahb_clock_enable(ar);
	if (ret) {
		ath10k_err(ar, "failed to enable clocks\n");
		return ret;
	}

	/* Clock for the target is supplied from outside of target (ie,
	 * external clock module controlled by the host). Target needs
	 * to know what frequency target cpu is configured which is needed
	 * for target internal use. Read target cpu frequency info from
	 * gcc register and write into target's scratch register where
	 * target expects this information.
	 */
	val = ath10k_ahb_gcc_read32(ar, ATH10K_AHB_GCC_FEPLL_PLL_DIV);
	ath10k_ahb_write32(ar, ATH10K_AHB_WIFI_SCRATCH_5_REG, val);

	ret = ath10k_ahb_release_reset(ar);
	if (ret)
		goto err_clk_disable;

	ath10k_ahb_irq_disable(ar);

	ath10k_ahb_write32(ar, FW_INDICATOR_ADDRESS, FW_IND_HOST_READY);

	ret = ath10k_pci_wait_for_target_init(ar);
	if (ret)
		goto err_halt_chip;

	return 0;

err_halt_chip:
	ath10k_ahb_halt_chip(ar);

err_clk_disable:
	ath10k_ahb_clock_disable(ar);

	return ret;
}