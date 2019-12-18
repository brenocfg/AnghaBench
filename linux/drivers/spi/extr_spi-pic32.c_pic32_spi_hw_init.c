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
struct pic32_spi {int fifo_n_byte; TYPE_1__* regs; } ;
struct TYPE_2__ {int /*<<< orphan*/  ctrl2_set; int /*<<< orphan*/  ctrl; } ;

/* Variables and functions */
 int CTRL2_FRM_ERR_EN ; 
 int CTRL2_RX_OV_EN ; 
 int CTRL2_TX_UR_EN ; 
 int CTRL_ENHBUF ; 
 int CTRL_FRMEN ; 
 int CTRL_MCLKSEL ; 
 int CTRL_MSSEN ; 
 int CTRL_MSTEN ; 
 int CTRL_RX_INT_SHIFT ; 
 int CTRL_TX_INT_SHIFT ; 
 int RX_FIFO_NOT_EMPTY ; 
 int TX_FIFO_HALF_EMPTY ; 
 int /*<<< orphan*/  pic32_spi_disable (struct pic32_spi*) ; 
 int readl (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  writel (int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void pic32_spi_hw_init(struct pic32_spi *pic32s)
{
	u32 ctrl;

	/* disable hardware */
	pic32_spi_disable(pic32s);

	ctrl = readl(&pic32s->regs->ctrl);
	/* enable enhanced fifo of 128bit deep */
	ctrl |= CTRL_ENHBUF;
	pic32s->fifo_n_byte = 16;

	/* disable framing mode */
	ctrl &= ~CTRL_FRMEN;

	/* enable master mode while disabled */
	ctrl |= CTRL_MSTEN;

	/* set tx fifo threshold interrupt */
	ctrl &= ~(0x3 << CTRL_TX_INT_SHIFT);
	ctrl |= (TX_FIFO_HALF_EMPTY << CTRL_TX_INT_SHIFT);

	/* set rx fifo threshold interrupt */
	ctrl &= ~(0x3 << CTRL_RX_INT_SHIFT);
	ctrl |= (RX_FIFO_NOT_EMPTY << CTRL_RX_INT_SHIFT);

	/* select clk source */
	ctrl &= ~CTRL_MCLKSEL;

	/* set manual /CS mode */
	ctrl &= ~CTRL_MSSEN;

	writel(ctrl, &pic32s->regs->ctrl);

	/* enable error reporting */
	ctrl = CTRL2_TX_UR_EN | CTRL2_RX_OV_EN | CTRL2_FRM_ERR_EN;
	writel(ctrl, &pic32s->regs->ctrl2_set);
}