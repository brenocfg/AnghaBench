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
typedef  int u32 ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  MV64340_BASE_ADDR_ENABLE ; 
 int /*<<< orphan*/  MV64340_INTEGRATED_SRAM_BASE_ADDR ; 
 int /*<<< orphan*/  MV64340_SRAM_CONFIG ; 
 int /*<<< orphan*/  MV643XX_ETH_BAR_4 ; 
 int /*<<< orphan*/  MV643XX_ETH_BASE_ADDR_ENABLE_REG ; 
 int /*<<< orphan*/  MV643XX_ETH_SIZE_REG_4 ; 
 int /*<<< orphan*/  MV_READ (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  MV_WRITE (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  PEGASOS2_MARVELL_REGBASE ; 
 int /*<<< orphan*/  PEGASOS2_MARVELL_REGSIZE ; 
 int PEGASOS2_SRAM_BASE ; 
 int PEGASOS2_SRAM_SIZE ; 
 int /*<<< orphan*/ * ioremap (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iounmap (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * mv643xx_reg_base ; 

__attribute__((used)) static int Enable_SRAM(void)
{
	u32 ALong;

	if (mv643xx_reg_base == NULL)
		mv643xx_reg_base = ioremap(PEGASOS2_MARVELL_REGBASE,
					PEGASOS2_MARVELL_REGSIZE);

	if (mv643xx_reg_base == NULL)
		return -ENOMEM;

#ifdef BE_VERBOSE
	printk("Pegasos II/Marvell MV64361: register remapped from %p to %p\n",
		(void *)PEGASOS2_MARVELL_REGBASE, (void *)mv643xx_reg_base);
#endif

	MV_WRITE(MV64340_SRAM_CONFIG, 0);

	MV_WRITE(MV64340_INTEGRATED_SRAM_BASE_ADDR, PEGASOS2_SRAM_BASE >> 16);

	MV_READ(MV64340_BASE_ADDR_ENABLE, ALong);
	ALong &= ~(1 << 19);
	MV_WRITE(MV64340_BASE_ADDR_ENABLE, ALong);

	ALong = 0x02;
	ALong |= PEGASOS2_SRAM_BASE & 0xffff0000;
	MV_WRITE(MV643XX_ETH_BAR_4, ALong);

	MV_WRITE(MV643XX_ETH_SIZE_REG_4, (PEGASOS2_SRAM_SIZE-1) & 0xffff0000);

	MV_READ(MV643XX_ETH_BASE_ADDR_ENABLE_REG, ALong);
	ALong &= ~(1 << 4);
	MV_WRITE(MV643XX_ETH_BASE_ADDR_ENABLE_REG, ALong);

#ifdef BE_VERBOSE
	printk("Pegasos II/Marvell MV64361: register unmapped\n");
	printk("Pegasos II/Marvell MV64361: SRAM at %p, size=%x\n", (void*) PEGASOS2_SRAM_BASE, PEGASOS2_SRAM_SIZE);
#endif

	iounmap(mv643xx_reg_base);
	mv643xx_reg_base = NULL;

	return 1;
}