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
struct ishtp_device {int dummy; } ;
struct ishtp_cl {scalar_t__ last_tx_path; scalar_t__ last_dma_acked; int /*<<< orphan*/  send_msg_cnt_ipc; scalar_t__ tx_offs; } ;

/* Variables and functions */
 scalar_t__ CL_TX_PATH_DMA ; 
 int /*<<< orphan*/  ipc_tx_callback (struct ishtp_cl*) ; 

__attribute__((used)) static void ishtp_cl_send_msg_ipc(struct ishtp_device *dev,
				  struct ishtp_cl *cl)
{
	/* If last DMA message wasn't acked yet, leave this one in Tx queue */
	if (cl->last_tx_path == CL_TX_PATH_DMA && cl->last_dma_acked == 0)
		return;

	cl->tx_offs = 0;
	ipc_tx_callback(cl);
	++cl->send_msg_cnt_ipc;
}