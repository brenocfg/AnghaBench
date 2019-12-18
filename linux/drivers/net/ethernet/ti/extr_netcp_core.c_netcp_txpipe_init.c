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
struct netcp_tx_pipe {char const* dma_chan_name; unsigned int dma_queue_id; struct netcp_device* netcp_device; } ;
struct netcp_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  memset (struct netcp_tx_pipe*,int /*<<< orphan*/ ,int) ; 

int netcp_txpipe_init(struct netcp_tx_pipe *tx_pipe,
		      struct netcp_device *netcp_device,
		      const char *dma_chan_name, unsigned int dma_queue_id)
{
	memset(tx_pipe, 0, sizeof(*tx_pipe));
	tx_pipe->netcp_device = netcp_device;
	tx_pipe->dma_chan_name = dma_chan_name;
	tx_pipe->dma_queue_id = dma_queue_id;
	return 0;
}