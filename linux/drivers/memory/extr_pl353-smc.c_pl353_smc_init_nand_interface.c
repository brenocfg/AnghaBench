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
struct device_node {int dummy; } ;
struct amba_device {int dummy; } ;

/* Variables and functions */
 unsigned long PL353_NAND_ECC_BUSY_TIMEOUT ; 
 int /*<<< orphan*/  PL353_NAND_ECC_CMD1 ; 
 int /*<<< orphan*/  PL353_NAND_ECC_CMD2 ; 
 int /*<<< orphan*/  PL353_SMC_CFG_CLR_INT_CLR_1 ; 
 scalar_t__ PL353_SMC_CFG_CLR_OFFS ; 
 int /*<<< orphan*/  PL353_SMC_DC_UPT_NAND_REGS ; 
 scalar_t__ PL353_SMC_DIRECT_CMD_OFFS ; 
 scalar_t__ PL353_SMC_ECC_MEMCMD1_OFFS ; 
 scalar_t__ PL353_SMC_ECC_MEMCMD2_OFFS ; 
 int /*<<< orphan*/  PL353_SMC_MEM_WIDTH_8 ; 
 int /*<<< orphan*/  cpu_relax () ; 
 unsigned long jiffies ; 
 scalar_t__ pl353_smc_base ; 
 scalar_t__ pl353_smc_ecc_is_busy () ; 
 int /*<<< orphan*/  pl353_smc_set_buswidth (int /*<<< orphan*/ ) ; 
 scalar_t__ time_after_eq (unsigned long,unsigned long) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void pl353_smc_init_nand_interface(struct amba_device *adev,
					  struct device_node *nand_node)
{
	unsigned long timeout;

	pl353_smc_set_buswidth(PL353_SMC_MEM_WIDTH_8);
	writel(PL353_SMC_CFG_CLR_INT_CLR_1,
	       pl353_smc_base + PL353_SMC_CFG_CLR_OFFS);
	writel(PL353_SMC_DC_UPT_NAND_REGS, pl353_smc_base +
	       PL353_SMC_DIRECT_CMD_OFFS);

	timeout = jiffies + PL353_NAND_ECC_BUSY_TIMEOUT;
	/* Wait till the ECC operation is complete */
	do {
		if (pl353_smc_ecc_is_busy())
			cpu_relax();
		else
			break;
	} while (!time_after_eq(jiffies, timeout));

	if (time_after_eq(jiffies, timeout))
		return;

	writel(PL353_NAND_ECC_CMD1,
	       pl353_smc_base + PL353_SMC_ECC_MEMCMD1_OFFS);
	writel(PL353_NAND_ECC_CMD2,
	       pl353_smc_base + PL353_SMC_ECC_MEMCMD2_OFFS);
}