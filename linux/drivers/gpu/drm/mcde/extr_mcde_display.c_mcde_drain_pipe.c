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
struct mcde {int regs; int /*<<< orphan*/  dev; } ;
typedef  enum mcde_fifo { ____Placeholder_mcde_fifo } mcde_fifo ;
typedef  enum mcde_channel { ____Placeholder_mcde_channel } mcde_channel ;

/* Variables and functions */
#define  MCDE_CHANNEL_0 133 
#define  MCDE_CHANNEL_1 132 
#define  MCDE_CHANNEL_2 131 
#define  MCDE_CHANNEL_3 130 
 int MCDE_CHNL0SYNCHSW ; 
 int MCDE_CHNL1SYNCHSW ; 
 int MCDE_CHNL2SYNCHSW ; 
 int MCDE_CHNL3SYNCHSW ; 
 int /*<<< orphan*/  MCDE_CHNLXSYNCHSW_SW_TRIG ; 
 int MCDE_CTRLA ; 
 int MCDE_CTRLB ; 
 int MCDE_CTRLX_FIFOEMPTY ; 
#define  MCDE_FIFO_A 129 
#define  MCDE_FIFO_B 128 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  mcde_disable_fifo (struct mcde*,int,int) ; 
 int /*<<< orphan*/  mcde_enable_fifo (struct mcde*,int) ; 
 int readl (int) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void mcde_drain_pipe(struct mcde *mcde, enum mcde_fifo fifo,
			    enum mcde_channel ch)
{
	u32 val;
	u32 ctrl;
	u32 synsw;

	switch (fifo) {
	case MCDE_FIFO_A:
		ctrl = MCDE_CTRLA;
		break;
	case MCDE_FIFO_B:
		ctrl = MCDE_CTRLB;
		break;
	}

	switch (ch) {
	case MCDE_CHANNEL_0:
		synsw = MCDE_CHNL0SYNCHSW;
		break;
	case MCDE_CHANNEL_1:
		synsw = MCDE_CHNL1SYNCHSW;
		break;
	case MCDE_CHANNEL_2:
		synsw = MCDE_CHNL2SYNCHSW;
		break;
	case MCDE_CHANNEL_3:
		synsw = MCDE_CHNL3SYNCHSW;
		return;
	}

	val = readl(mcde->regs + ctrl);
	if (!(val & MCDE_CTRLX_FIFOEMPTY)) {
		dev_err(mcde->dev, "Channel A FIFO not empty (handover)\n");
		/* Attempt to clear the FIFO */
		mcde_enable_fifo(mcde, fifo);
		/* Trigger a software sync out on respective channel (0-3) */
		writel(MCDE_CHNLXSYNCHSW_SW_TRIG, mcde->regs + synsw);
		/* Disable FIFO A flow again */
		mcde_disable_fifo(mcde, fifo, true);
	}
}