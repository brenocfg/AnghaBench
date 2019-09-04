#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct net_device {int dummy; } ;
struct TYPE_5__ {int mask; struct mcp_kreq_ether_send* req_list; TYPE_2__* req_bytes; TYPE_2__* info; scalar_t__ queue_active; } ;
struct TYPE_7__ {int mask; int cnt; int fill_cnt; TYPE_2__* shadow; TYPE_2__* info; scalar_t__ watchdog_needed; void* page_offset; } ;
struct myri10ge_slice_state {TYPE_1__ tx; TYPE_3__ rx_small; TYPE_3__ rx_big; struct myri10ge_priv* mgp; } ;
struct myri10ge_priv {scalar_t__ small_bytes; scalar_t__ big_bytes; int /*<<< orphan*/  pdev; struct myri10ge_slice_state* ss; struct net_device* dev; } ;
struct myri10ge_cmd {int data0; } ;
struct mcp_kreq_ether_send {int dummy; } ;
struct mcp_dma_addr {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/  page; } ;

/* Variables and functions */
 scalar_t__ ALIGN (unsigned long,int) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  MXGEFW_CMD_GET_RX_RING_SIZE ; 
 int /*<<< orphan*/  MXGEFW_CMD_GET_SEND_RING_SIZE ; 
 scalar_t__ MXGEFW_PAD ; 
 void* MYRI10GE_ALLOC_SIZE ; 
 int MYRI10GE_MAX_SEND_DESC_TSO ; 
 int /*<<< orphan*/  kfree (TYPE_2__*) ; 
 void* kzalloc (size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  myri10ge_alloc_rx_pages (struct myri10ge_priv*,TYPE_3__*,scalar_t__,int /*<<< orphan*/ ) ; 
 int myri10ge_send_cmd (struct myri10ge_priv*,int /*<<< orphan*/ ,struct myri10ge_cmd*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  myri10ge_unmap_rx_page (int /*<<< orphan*/ ,TYPE_2__*,scalar_t__) ; 
 int /*<<< orphan*/  netdev_err (struct net_device*,char*,int,int) ; 
 int /*<<< orphan*/  put_page (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int myri10ge_allocate_rings(struct myri10ge_slice_state *ss)
{
	struct myri10ge_priv *mgp = ss->mgp;
	struct myri10ge_cmd cmd;
	struct net_device *dev = mgp->dev;
	int tx_ring_size, rx_ring_size;
	int tx_ring_entries, rx_ring_entries;
	int i, slice, status;
	size_t bytes;

	/* get ring sizes */
	slice = ss - mgp->ss;
	cmd.data0 = slice;
	status = myri10ge_send_cmd(mgp, MXGEFW_CMD_GET_SEND_RING_SIZE, &cmd, 0);
	tx_ring_size = cmd.data0;
	cmd.data0 = slice;
	status |= myri10ge_send_cmd(mgp, MXGEFW_CMD_GET_RX_RING_SIZE, &cmd, 0);
	if (status != 0)
		return status;
	rx_ring_size = cmd.data0;

	tx_ring_entries = tx_ring_size / sizeof(struct mcp_kreq_ether_send);
	rx_ring_entries = rx_ring_size / sizeof(struct mcp_dma_addr);
	ss->tx.mask = tx_ring_entries - 1;
	ss->rx_small.mask = ss->rx_big.mask = rx_ring_entries - 1;

	status = -ENOMEM;

	/* allocate the host shadow rings */

	bytes = 8 + (MYRI10GE_MAX_SEND_DESC_TSO + 4)
	    * sizeof(*ss->tx.req_list);
	ss->tx.req_bytes = kzalloc(bytes, GFP_KERNEL);
	if (ss->tx.req_bytes == NULL)
		goto abort_with_nothing;

	/* ensure req_list entries are aligned to 8 bytes */
	ss->tx.req_list = (struct mcp_kreq_ether_send *)
	    ALIGN((unsigned long)ss->tx.req_bytes, 8);
	ss->tx.queue_active = 0;

	bytes = rx_ring_entries * sizeof(*ss->rx_small.shadow);
	ss->rx_small.shadow = kzalloc(bytes, GFP_KERNEL);
	if (ss->rx_small.shadow == NULL)
		goto abort_with_tx_req_bytes;

	bytes = rx_ring_entries * sizeof(*ss->rx_big.shadow);
	ss->rx_big.shadow = kzalloc(bytes, GFP_KERNEL);
	if (ss->rx_big.shadow == NULL)
		goto abort_with_rx_small_shadow;

	/* allocate the host info rings */

	bytes = tx_ring_entries * sizeof(*ss->tx.info);
	ss->tx.info = kzalloc(bytes, GFP_KERNEL);
	if (ss->tx.info == NULL)
		goto abort_with_rx_big_shadow;

	bytes = rx_ring_entries * sizeof(*ss->rx_small.info);
	ss->rx_small.info = kzalloc(bytes, GFP_KERNEL);
	if (ss->rx_small.info == NULL)
		goto abort_with_tx_info;

	bytes = rx_ring_entries * sizeof(*ss->rx_big.info);
	ss->rx_big.info = kzalloc(bytes, GFP_KERNEL);
	if (ss->rx_big.info == NULL)
		goto abort_with_rx_small_info;

	/* Fill the receive rings */
	ss->rx_big.cnt = 0;
	ss->rx_small.cnt = 0;
	ss->rx_big.fill_cnt = 0;
	ss->rx_small.fill_cnt = 0;
	ss->rx_small.page_offset = MYRI10GE_ALLOC_SIZE;
	ss->rx_big.page_offset = MYRI10GE_ALLOC_SIZE;
	ss->rx_small.watchdog_needed = 0;
	ss->rx_big.watchdog_needed = 0;
	if (mgp->small_bytes == 0) {
		ss->rx_small.fill_cnt = ss->rx_small.mask + 1;
	} else {
		myri10ge_alloc_rx_pages(mgp, &ss->rx_small,
					mgp->small_bytes + MXGEFW_PAD, 0);
	}

	if (ss->rx_small.fill_cnt < ss->rx_small.mask + 1) {
		netdev_err(dev, "slice-%d: alloced only %d small bufs\n",
			   slice, ss->rx_small.fill_cnt);
		goto abort_with_rx_small_ring;
	}

	myri10ge_alloc_rx_pages(mgp, &ss->rx_big, mgp->big_bytes, 0);
	if (ss->rx_big.fill_cnt < ss->rx_big.mask + 1) {
		netdev_err(dev, "slice-%d: alloced only %d big bufs\n",
			   slice, ss->rx_big.fill_cnt);
		goto abort_with_rx_big_ring;
	}

	return 0;

abort_with_rx_big_ring:
	for (i = ss->rx_big.cnt; i < ss->rx_big.fill_cnt; i++) {
		int idx = i & ss->rx_big.mask;
		myri10ge_unmap_rx_page(mgp->pdev, &ss->rx_big.info[idx],
				       mgp->big_bytes);
		put_page(ss->rx_big.info[idx].page);
	}

abort_with_rx_small_ring:
	if (mgp->small_bytes == 0)
		ss->rx_small.fill_cnt = ss->rx_small.cnt;
	for (i = ss->rx_small.cnt; i < ss->rx_small.fill_cnt; i++) {
		int idx = i & ss->rx_small.mask;
		myri10ge_unmap_rx_page(mgp->pdev, &ss->rx_small.info[idx],
				       mgp->small_bytes + MXGEFW_PAD);
		put_page(ss->rx_small.info[idx].page);
	}

	kfree(ss->rx_big.info);

abort_with_rx_small_info:
	kfree(ss->rx_small.info);

abort_with_tx_info:
	kfree(ss->tx.info);

abort_with_rx_big_shadow:
	kfree(ss->rx_big.shadow);

abort_with_rx_small_shadow:
	kfree(ss->rx_small.shadow);

abort_with_tx_req_bytes:
	kfree(ss->tx.req_bytes);
	ss->tx.req_bytes = NULL;
	ss->tx.req_list = NULL;

abort_with_nothing:
	return status;
}