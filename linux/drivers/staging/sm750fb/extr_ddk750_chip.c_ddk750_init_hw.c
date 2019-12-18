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
struct initchip_param {scalar_t__ powerMode; unsigned int memClock; unsigned int masterClock; int resetMemory; int setAllEngOff; scalar_t__ chipClock; } ;

/* Variables and functions */
 int /*<<< orphan*/  ALPHA_DISPLAY_CTRL ; 
 int /*<<< orphan*/  CURRENT_GATE ; 
 unsigned int CURRENT_GATE_DISPLAY ; 
 unsigned int CURRENT_GATE_LOCALMEM ; 
 unsigned int DISPLAY_CTRL_PLANE ; 
 int /*<<< orphan*/  DMA_ABORT_INTERRUPT ; 
 unsigned int DMA_ABORT_INTERRUPT_ABORT_1 ; 
 int /*<<< orphan*/  MHz (unsigned int) ; 
 int /*<<< orphan*/  MISC_CTRL ; 
 unsigned int MISC_CTRL_LOCALMEM_RESET ; 
 scalar_t__ SM750LE ; 
 int /*<<< orphan*/  VGA_CONFIGURATION ; 
 unsigned int VGA_CONFIGURATION_MODE ; 
 unsigned int VGA_CONFIGURATION_PLL ; 
 int /*<<< orphan*/  VIDEO_ALPHA_DISPLAY_CTRL ; 
 int /*<<< orphan*/  VIDEO_DISPLAY_CTRL ; 
 int /*<<< orphan*/  outb_p (int,int) ; 
 unsigned int peek32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  poke32 (int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  set_chip_clock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_master_clock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_memory_clock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sm750_enable_2d_engine (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sm750_enable_dma (int /*<<< orphan*/ ) ; 
 scalar_t__ sm750_get_chip_type () ; 
 int /*<<< orphan*/  sm750_set_current_gate (unsigned int) ; 
 int /*<<< orphan*/  sm750_set_power_mode (scalar_t__) ; 

int ddk750_init_hw(struct initchip_param *pInitParam)
{
	unsigned int reg;

	if (pInitParam->powerMode != 0)
		pInitParam->powerMode = 0;
	sm750_set_power_mode(pInitParam->powerMode);

	/* Enable display power gate & LOCALMEM power gate*/
	reg = peek32(CURRENT_GATE);
	reg |= (CURRENT_GATE_DISPLAY | CURRENT_GATE_LOCALMEM);
	sm750_set_current_gate(reg);

	if (sm750_get_chip_type() != SM750LE) {
		/* set panel pll and graphic mode via mmio_88 */
		reg = peek32(VGA_CONFIGURATION);
		reg |= (VGA_CONFIGURATION_PLL | VGA_CONFIGURATION_MODE);
		poke32(VGA_CONFIGURATION, reg);
	} else {
#if defined(__i386__) || defined(__x86_64__)
		/* set graphic mode via IO method */
		outb_p(0x88, 0x3d4);
		outb_p(0x06, 0x3d5);
#endif
	}

	/* Set the Main Chip Clock */
	set_chip_clock(MHz((unsigned int)pInitParam->chipClock));

	/* Set up memory clock. */
	set_memory_clock(MHz(pInitParam->memClock));

	/* Set up master clock */
	set_master_clock(MHz(pInitParam->masterClock));

	/*
	 * Reset the memory controller.
	 * If the memory controller is not reset in SM750,
	 * the system might hang when sw accesses the memory.
	 * The memory should be resetted after changing the MXCLK.
	 */
	if (pInitParam->resetMemory == 1) {
		reg = peek32(MISC_CTRL);
		reg &= ~MISC_CTRL_LOCALMEM_RESET;
		poke32(MISC_CTRL, reg);

		reg |= MISC_CTRL_LOCALMEM_RESET;
		poke32(MISC_CTRL, reg);
	}

	if (pInitParam->setAllEngOff == 1) {
		sm750_enable_2d_engine(0);

		/* Disable Overlay, if a former application left it on */
		reg = peek32(VIDEO_DISPLAY_CTRL);
		reg &= ~DISPLAY_CTRL_PLANE;
		poke32(VIDEO_DISPLAY_CTRL, reg);

		/* Disable video alpha, if a former application left it on */
		reg = peek32(VIDEO_ALPHA_DISPLAY_CTRL);
		reg &= ~DISPLAY_CTRL_PLANE;
		poke32(VIDEO_ALPHA_DISPLAY_CTRL, reg);

		/* Disable alpha plane, if a former application left it on */
		reg = peek32(ALPHA_DISPLAY_CTRL);
		reg &= ~DISPLAY_CTRL_PLANE;
		poke32(ALPHA_DISPLAY_CTRL, reg);

		/* Disable DMA Channel, if a former application left it on */
		reg = peek32(DMA_ABORT_INTERRUPT);
		reg |= DMA_ABORT_INTERRUPT_ABORT_1;
		poke32(DMA_ABORT_INTERRUPT, reg);

		/* Disable DMA Power, if a former application left it on */
		sm750_enable_dma(0);
	}

	/* We can add more initialization as needed. */

	return 0;
}