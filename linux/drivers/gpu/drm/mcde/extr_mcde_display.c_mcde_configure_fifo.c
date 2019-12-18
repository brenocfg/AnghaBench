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
struct mcde {int regs; } ;
typedef  enum mcde_fifo { ____Placeholder_mcde_fifo } mcde_fifo ;
typedef  enum mcde_dsi_formatter { ____Placeholder_mcde_dsi_formatter } mcde_dsi_formatter ;

/* Variables and functions */
 int MCDE_CRA0 ; 
 int MCDE_CRA1 ; 
 int MCDE_CRB0 ; 
 int MCDE_CRB1 ; 
 int MCDE_CRX0_ALPHABLEND_SHIFT ; 
 int MCDE_CRX0_BLENDEN ; 
 int MCDE_CRX1_CLKSEL_MCDECLK ; 
 int MCDE_CRX1_CLKSEL_SHIFT ; 
 int MCDE_CTRLA ; 
 int MCDE_CTRLB ; 
 int MCDE_CTRLX_FIFOWTRMRK_SHIFT ; 
 int MCDE_CTRLX_FORMID_SHIFT ; 
 int MCDE_CTRLX_FORMTYPE_DSI ; 
 int MCDE_CTRLX_FORMTYPE_SHIFT ; 
#define  MCDE_FIFO_A 129 
#define  MCDE_FIFO_B 128 
 int /*<<< orphan*/  writel (int,int) ; 

__attribute__((used)) static void mcde_configure_fifo(struct mcde *mcde, enum mcde_fifo fifo,
				enum mcde_dsi_formatter fmt,
				int fifo_wtrmrk)
{
	u32 val;
	u32 ctrl;
	u32 cr0, cr1;

	switch (fifo) {
	case MCDE_FIFO_A:
		ctrl = MCDE_CTRLA;
		cr0 = MCDE_CRA0;
		cr1 = MCDE_CRA1;
		break;
	case MCDE_FIFO_B:
		ctrl = MCDE_CTRLB;
		cr0 = MCDE_CRB0;
		cr1 = MCDE_CRB1;
		break;
	}

	val = fifo_wtrmrk << MCDE_CTRLX_FIFOWTRMRK_SHIFT;
	/* We only support DSI formatting for now */
	val |= MCDE_CTRLX_FORMTYPE_DSI <<
		MCDE_CTRLX_FORMTYPE_SHIFT;

	/* Select the formatter to use for this FIFO */
	val |= fmt << MCDE_CTRLX_FORMID_SHIFT;
	writel(val, mcde->regs + ctrl);

	/* Blend source with Alpha 0xff on FIFO */
	val = MCDE_CRX0_BLENDEN |
		0xff << MCDE_CRX0_ALPHABLEND_SHIFT;
	writel(val, mcde->regs + cr0);

	/* Set-up from mcde_fmtr_dsi.c, fmtr_dsi_enable_video() */

	/* Use the MCDE clock for this FIFO */
	val = MCDE_CRX1_CLKSEL_MCDECLK << MCDE_CRX1_CLKSEL_SHIFT;

	/* TODO: when adding DPI support add OUTBPP etc here */
	writel(val, mcde->regs + cr1);
}