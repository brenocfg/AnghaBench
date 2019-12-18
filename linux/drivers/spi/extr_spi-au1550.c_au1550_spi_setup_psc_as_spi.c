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
typedef  int u32 ;
struct au1550_spi {TYPE_1__* regs; scalar_t__ usedma; } ;
struct TYPE_2__ {int psc_spicfg; int psc_spistat; int /*<<< orphan*/  psc_ctrl; int /*<<< orphan*/  psc_sel; } ;

/* Variables and functions */
 int /*<<< orphan*/  PSC_CTRL_DISABLE ; 
 int /*<<< orphan*/  PSC_CTRL_ENABLE ; 
 int /*<<< orphan*/  PSC_SEL_PS_SPIMODE ; 
 int PSC_SPICFG_DD_DISABLE ; 
 int PSC_SPICFG_DE_ENABLE ; 
 int PSC_SPICFG_LB ; 
 int PSC_SPICFG_RT_FIFO8 ; 
 int PSC_SPICFG_SET_BAUD (int) ; 
 int PSC_SPICFG_SET_DIV (int /*<<< orphan*/ ) ; 
 int PSC_SPICFG_SET_LEN (int) ; 
 int PSC_SPICFG_TT_FIFO8 ; 
 int PSC_SPISTAT_DR ; 
 int PSC_SPISTAT_SR ; 
 int /*<<< orphan*/  au1550_spi_mask_ack_all (struct au1550_spi*) ; 
 int /*<<< orphan*/  au1550_spi_reset_fifos (struct au1550_spi*) ; 
 int /*<<< orphan*/  wmb () ; 

__attribute__((used)) static void au1550_spi_setup_psc_as_spi(struct au1550_spi *hw)
{
	u32 stat, cfg;

	/* set up the PSC for SPI mode */
	hw->regs->psc_ctrl = PSC_CTRL_DISABLE;
	wmb(); /* drain writebuffer */
	hw->regs->psc_sel = PSC_SEL_PS_SPIMODE;
	wmb(); /* drain writebuffer */

	hw->regs->psc_spicfg = 0;
	wmb(); /* drain writebuffer */

	hw->regs->psc_ctrl = PSC_CTRL_ENABLE;
	wmb(); /* drain writebuffer */

	do {
		stat = hw->regs->psc_spistat;
		wmb(); /* drain writebuffer */
	} while ((stat & PSC_SPISTAT_SR) == 0);


	cfg = hw->usedma ? 0 : PSC_SPICFG_DD_DISABLE;
	cfg |= PSC_SPICFG_SET_LEN(8);
	cfg |= PSC_SPICFG_RT_FIFO8 | PSC_SPICFG_TT_FIFO8;
	/* use minimal allowed brg and div values as initial setting: */
	cfg |= PSC_SPICFG_SET_BAUD(4) | PSC_SPICFG_SET_DIV(0);

#ifdef AU1550_SPI_DEBUG_LOOPBACK
	cfg |= PSC_SPICFG_LB;
#endif

	hw->regs->psc_spicfg = cfg;
	wmb(); /* drain writebuffer */

	au1550_spi_mask_ack_all(hw);

	hw->regs->psc_spicfg |= PSC_SPICFG_DE_ENABLE;
	wmb(); /* drain writebuffer */

	do {
		stat = hw->regs->psc_spistat;
		wmb(); /* drain writebuffer */
	} while ((stat & PSC_SPISTAT_DR) == 0);

	au1550_spi_reset_fifos(hw);
}