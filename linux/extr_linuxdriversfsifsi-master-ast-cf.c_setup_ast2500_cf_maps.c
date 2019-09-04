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
struct fsi_master_acf {int cf_mem_addr; int /*<<< orphan*/  scu; } ;

/* Variables and functions */
 int /*<<< orphan*/  SCU_2500_COPRO_CACHE_CTL ; 
 int SCU_2500_COPRO_CACHE_EN ; 
 int /*<<< orphan*/  SCU_2500_COPRO_SEG0 ; 
 int SCU_2500_COPRO_SEG0_CACHE_EN ; 
 int /*<<< orphan*/  SCU_2500_COPRO_SEG2 ; 
 int /*<<< orphan*/  SCU_2500_COPRO_SEG3 ; 
 int /*<<< orphan*/  SCU_2500_COPRO_SEG6 ; 
 int /*<<< orphan*/  SCU_2500_COPRO_SEG7 ; 
 int SCU_2500_COPRO_SEG_SWAP ; 
 int SYSREG_BASE ; 
 int /*<<< orphan*/  regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void setup_ast2500_cf_maps(struct fsi_master_acf *master)
{
	/*
	 * Note about byteswap setting: the bus is wired backwards,
	 * so setting the byteswap bit actually makes the ColdFire
	 * work "normally" for a BE processor, ie, put the MSB in
	 * the lowest address byte.
	 *
	 * We thus need to set the bit for our main memory which
	 * contains our program code. We create two mappings for
	 * the register, one with each setting.
	 *
	 * Segments 2 and 3 has a "swapped" mapping (BE)
	 * and 6 and 7 have a non-swapped mapping (LE) which allows
	 * us to avoid byteswapping register accesses since the
	 * registers are all LE.
	 */

	/* Setup segment 0 to our memory region */
	regmap_write(master->scu, SCU_2500_COPRO_SEG0, master->cf_mem_addr |
		     SCU_2500_COPRO_SEG_SWAP);

	/* Segments 2 and 3 to sysregs with byteswap (for SRAM) */
	regmap_write(master->scu, SCU_2500_COPRO_SEG2, SYSREG_BASE |
		     SCU_2500_COPRO_SEG_SWAP);
	regmap_write(master->scu, SCU_2500_COPRO_SEG3, SYSREG_BASE | 0x100000 |
		     SCU_2500_COPRO_SEG_SWAP);

	/* And segment 6 and 7 to sysregs no byteswap */
	regmap_write(master->scu, SCU_2500_COPRO_SEG6, SYSREG_BASE);
	regmap_write(master->scu, SCU_2500_COPRO_SEG7, SYSREG_BASE | 0x100000);

	/* Memory cachable, regs and SRAM not cachable */
	regmap_write(master->scu, SCU_2500_COPRO_CACHE_CTL,
		     SCU_2500_COPRO_SEG0_CACHE_EN | SCU_2500_COPRO_CACHE_EN);
}