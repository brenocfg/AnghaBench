#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct vnt_tx_desc {TYPE_2__* td_info; void* next_desc; struct vnt_tx_desc* next; } ;
struct TYPE_4__ {int* tx_descs; } ;
struct vnt_private {struct vnt_tx_desc* apTD0Rings; struct vnt_tx_desc** apCurrTD; struct vnt_tx_desc** apTailTD; scalar_t__ td0_pool_dma; TYPE_1__ opts; scalar_t__ tx_bufs_dma0; scalar_t__ tx0_bufs; } ;
typedef  scalar_t__ dma_addr_t ;
struct TYPE_5__ {scalar_t__ buf_dma; scalar_t__ buf; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int PKT_BUF_SZ ; 
 void* cpu_to_le32 (scalar_t__) ; 
 int /*<<< orphan*/  kfree (TYPE_2__*) ; 
 TYPE_2__* kzalloc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int device_init_td0_ring(struct vnt_private *priv)
{
	int i;
	dma_addr_t  curr;
	struct vnt_tx_desc *desc;
	int ret;

	curr = priv->td0_pool_dma;
	for (i = 0; i < priv->opts.tx_descs[0];
	     i++, curr += sizeof(struct vnt_tx_desc)) {
		desc = &priv->apTD0Rings[i];
		desc->td_info = kzalloc(sizeof(*desc->td_info), GFP_KERNEL);
		if (!desc->td_info) {
			ret = -ENOMEM;
			goto err_free_desc;
		}

		desc->td_info->buf = priv->tx0_bufs + i * PKT_BUF_SZ;
		desc->td_info->buf_dma = priv->tx_bufs_dma0 + i * PKT_BUF_SZ;

		desc->next = &(priv->apTD0Rings[(i+1) % priv->opts.tx_descs[0]]);
		desc->next_desc = cpu_to_le32(curr + sizeof(struct vnt_tx_desc));
	}

	if (i > 0)
		priv->apTD0Rings[i-1].next_desc = cpu_to_le32(priv->td0_pool_dma);
	priv->apTailTD[0] = priv->apCurrTD[0] = &priv->apTD0Rings[0];

	return 0;

err_free_desc:
	while (--i) {
		desc = &priv->apTD0Rings[i];
		kfree(desc->td_info);
	}

	return ret;
}