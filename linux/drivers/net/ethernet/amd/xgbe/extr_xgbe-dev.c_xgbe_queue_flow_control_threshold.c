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
struct xgbe_prv_data {unsigned int pfc_rfa; int* rx_rfa; int* rx_rfd; scalar_t__* pfcq; } ;

/* Variables and functions */
 unsigned int XGMAC_FLOW_CONTROL_ALIGN (int /*<<< orphan*/ ) ; 
 unsigned int XGMAC_FLOW_CONTROL_MAX ; 
 unsigned int XGMAC_FLOW_CONTROL_UNIT ; 
 void* XGMAC_FLOW_CONTROL_VALUE (unsigned int) ; 
 int /*<<< orphan*/  xgbe_get_max_frame (struct xgbe_prv_data*) ; 

__attribute__((used)) static void xgbe_queue_flow_control_threshold(struct xgbe_prv_data *pdata,
					      unsigned int queue,
					      unsigned int q_fifo_size)
{
	unsigned int frame_fifo_size;
	unsigned int rfa, rfd;

	frame_fifo_size = XGMAC_FLOW_CONTROL_ALIGN(xgbe_get_max_frame(pdata));

	if (pdata->pfcq[queue] && (q_fifo_size > pdata->pfc_rfa)) {
		/* PFC is active for this queue */
		rfa = pdata->pfc_rfa;
		rfd = rfa + frame_fifo_size;
		if (rfd > XGMAC_FLOW_CONTROL_MAX)
			rfd = XGMAC_FLOW_CONTROL_MAX;
		if (rfa >= XGMAC_FLOW_CONTROL_MAX)
			rfa = XGMAC_FLOW_CONTROL_MAX - XGMAC_FLOW_CONTROL_UNIT;
	} else {
		/* This path deals with just maximum frame sizes which are
		 * limited to a jumbo frame of 9,000 (plus headers, etc.)
		 * so we can never exceed the maximum allowable RFA/RFD
		 * values.
		 */
		if (q_fifo_size <= 2048) {
			/* rx_rfd to zero to signal no flow control */
			pdata->rx_rfa[queue] = 0;
			pdata->rx_rfd[queue] = 0;
			return;
		}

		if (q_fifo_size <= 4096) {
			/* Between 2048 and 4096 */
			pdata->rx_rfa[queue] = 0;	/* Full - 1024 bytes */
			pdata->rx_rfd[queue] = 1;	/* Full - 1536 bytes */
			return;
		}

		if (q_fifo_size <= frame_fifo_size) {
			/* Between 4096 and max-frame */
			pdata->rx_rfa[queue] = 2;	/* Full - 2048 bytes */
			pdata->rx_rfd[queue] = 5;	/* Full - 3584 bytes */
			return;
		}

		if (q_fifo_size <= (frame_fifo_size * 3)) {
			/* Between max-frame and 3 max-frames,
			 * trigger if we get just over a frame of data and
			 * resume when we have just under half a frame left.
			 */
			rfa = q_fifo_size - frame_fifo_size;
			rfd = rfa + (frame_fifo_size / 2);
		} else {
			/* Above 3 max-frames - trigger when just over
			 * 2 frames of space available
			 */
			rfa = frame_fifo_size * 2;
			rfa += XGMAC_FLOW_CONTROL_UNIT;
			rfd = rfa + frame_fifo_size;
		}
	}

	pdata->rx_rfa[queue] = XGMAC_FLOW_CONTROL_VALUE(rfa);
	pdata->rx_rfd[queue] = XGMAC_FLOW_CONTROL_VALUE(rfd);
}