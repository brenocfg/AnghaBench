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
struct TYPE_2__ {int /*<<< orphan*/  tx_submit; } ;
struct msgdma_sw_desc {int /*<<< orphan*/  node; TYPE_1__ async_tx; } ;
struct msgdma_device {int idle; int desc_free_cnt; int /*<<< orphan*/  free_list; int /*<<< orphan*/  dmachan; struct msgdma_sw_desc* sw_desq; } ;
struct dma_chan {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_NOWAIT ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int MSGDMA_DESC_NUM ; 
 int /*<<< orphan*/  dma_async_tx_descriptor_init (TYPE_1__*,int /*<<< orphan*/ *) ; 
 struct msgdma_sw_desc* kcalloc (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  msgdma_tx_submit ; 
 struct msgdma_device* to_mdev (struct dma_chan*) ; 

__attribute__((used)) static int msgdma_alloc_chan_resources(struct dma_chan *dchan)
{
	struct msgdma_device *mdev = to_mdev(dchan);
	struct msgdma_sw_desc *desc;
	int i;

	mdev->sw_desq = kcalloc(MSGDMA_DESC_NUM, sizeof(*desc), GFP_NOWAIT);
	if (!mdev->sw_desq)
		return -ENOMEM;

	mdev->idle = true;
	mdev->desc_free_cnt = MSGDMA_DESC_NUM;

	INIT_LIST_HEAD(&mdev->free_list);

	for (i = 0; i < MSGDMA_DESC_NUM; i++) {
		desc = mdev->sw_desq + i;
		dma_async_tx_descriptor_init(&desc->async_tx, &mdev->dmachan);
		desc->async_tx.tx_submit = msgdma_tx_submit;
		list_add_tail(&desc->node, &mdev->free_list);
	}

	return MSGDMA_DESC_NUM;
}