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
struct vc4_dsi {int /*<<< orphan*/  xfer_result; int /*<<< orphan*/  xfer_completion; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int DSI1_INT_ERR_CONTROL ; 
 int DSI1_INT_ERR_CONT_LP0 ; 
 int DSI1_INT_ERR_CONT_LP1 ; 
 int DSI1_INT_ERR_SYNC_ESC ; 
 int DSI1_INT_HSTX_TO ; 
 int DSI1_INT_LPRX_TO ; 
 int DSI1_INT_PHY_DIR_RTF ; 
 int DSI1_INT_PR_TO ; 
 int DSI1_INT_TA_TO ; 
 int DSI1_INT_TXPKT1_DONE ; 
 int DSI_PORT_READ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DSI_PORT_WRITE (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ETIMEDOUT ; 
 int /*<<< orphan*/  INT_STAT ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dsi_handle_error (struct vc4_dsi*,int /*<<< orphan*/ *,int,int,char*) ; 

__attribute__((used)) static irqreturn_t vc4_dsi_irq_handler(int irq, void *data)
{
	struct vc4_dsi *dsi = data;
	u32 stat = DSI_PORT_READ(INT_STAT);
	irqreturn_t ret = IRQ_NONE;

	DSI_PORT_WRITE(INT_STAT, stat);

	dsi_handle_error(dsi, &ret, stat,
			 DSI1_INT_ERR_SYNC_ESC, "LPDT sync");
	dsi_handle_error(dsi, &ret, stat,
			 DSI1_INT_ERR_CONTROL, "data lane 0 sequence");
	dsi_handle_error(dsi, &ret, stat,
			 DSI1_INT_ERR_CONT_LP0, "LP0 contention");
	dsi_handle_error(dsi, &ret, stat,
			 DSI1_INT_ERR_CONT_LP1, "LP1 contention");
	dsi_handle_error(dsi, &ret, stat,
			 DSI1_INT_HSTX_TO, "HSTX timeout");
	dsi_handle_error(dsi, &ret, stat,
			 DSI1_INT_LPRX_TO, "LPRX timeout");
	dsi_handle_error(dsi, &ret, stat,
			 DSI1_INT_TA_TO, "turnaround timeout");
	dsi_handle_error(dsi, &ret, stat,
			 DSI1_INT_PR_TO, "peripheral reset timeout");

	if (stat & (DSI1_INT_TXPKT1_DONE | DSI1_INT_PHY_DIR_RTF)) {
		complete(&dsi->xfer_completion);
		ret = IRQ_HANDLED;
	} else if (stat & DSI1_INT_HSTX_TO) {
		complete(&dsi->xfer_completion);
		dsi->xfer_result = -ETIMEDOUT;
		ret = IRQ_HANDLED;
	}

	return ret;
}