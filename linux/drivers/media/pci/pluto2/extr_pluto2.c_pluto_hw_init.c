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
struct pluto {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MISC_ALED ; 
 int /*<<< orphan*/  PID0_END ; 
 int /*<<< orphan*/  REG_MISC ; 
 int /*<<< orphan*/  REG_PIDn (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pluto_dma_map (struct pluto*) ; 
 int /*<<< orphan*/  pluto_enable_irqs (struct pluto*) ; 
 int /*<<< orphan*/  pluto_reset_frontend (struct pluto*,int) ; 
 int /*<<< orphan*/  pluto_reset_ts (struct pluto*,int) ; 
 int /*<<< orphan*/  pluto_rw (struct pluto*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pluto_set_dma_addr (struct pluto*) ; 

__attribute__((used)) static int pluto_hw_init(struct pluto *pluto)
{
	pluto_reset_frontend(pluto, 1);

	/* set automatic LED control by FPGA */
	pluto_rw(pluto, REG_MISC, MISC_ALED, MISC_ALED);

	/* set data endianness */
#ifdef __LITTLE_ENDIAN
	pluto_rw(pluto, REG_PIDn(0), PID0_END, PID0_END);
#else
	pluto_rw(pluto, REG_PIDn(0), PID0_END, 0);
#endif
	/* map DMA and set address */
	pluto_dma_map(pluto);
	pluto_set_dma_addr(pluto);

	/* enable interrupts */
	pluto_enable_irqs(pluto);

	/* reset TS logic */
	pluto_reset_ts(pluto, 1);

	return 0;
}