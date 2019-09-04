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
struct pluto {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  REG_TSCR ; 
 int TSCR_DEM ; 
 int TSCR_IACK ; 
 int TSCR_MSKA ; 
 int TSCR_MSKL ; 
 int TSCR_MSKO ; 
 int pluto_readreg (struct pluto*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pluto_write_tscr (struct pluto*,int) ; 

__attribute__((used)) static void pluto_enable_irqs(struct pluto *pluto)
{
	u32 val = pluto_readreg(pluto, REG_TSCR);

	/* disable AFUL and LOCK interrupts */
	val |= (TSCR_MSKA | TSCR_MSKL);
	/* enable DMA and OVERFLOW interrupts */
	val &= ~(TSCR_DEM | TSCR_MSKO);
	/* clear pending interrupts */
	val |= TSCR_IACK;

	pluto_write_tscr(pluto, val);
}