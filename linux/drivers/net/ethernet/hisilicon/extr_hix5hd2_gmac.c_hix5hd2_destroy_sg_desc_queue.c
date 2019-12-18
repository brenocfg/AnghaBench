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
struct sg_desc {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/ * desc; int /*<<< orphan*/  phys_addr; } ;
struct hix5hd2_priv {TYPE_1__ tx_ring; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int TX_DESC_NUM ; 
 int /*<<< orphan*/  dma_free_coherent (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void hix5hd2_destroy_sg_desc_queue(struct hix5hd2_priv *priv)
{
	if (priv->tx_ring.desc) {
		dma_free_coherent(priv->dev,
				  TX_DESC_NUM * sizeof(struct sg_desc),
				  priv->tx_ring.desc, priv->tx_ring.phys_addr);
		priv->tx_ring.desc = NULL;
	}
}