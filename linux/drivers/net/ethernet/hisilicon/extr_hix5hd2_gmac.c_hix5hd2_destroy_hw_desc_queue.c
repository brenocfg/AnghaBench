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
struct hix5hd2_priv {TYPE_1__* pool; int /*<<< orphan*/  dev; } ;
struct TYPE_2__ {int /*<<< orphan*/ * desc; int /*<<< orphan*/  phys_addr; int /*<<< orphan*/  size; } ;

/* Variables and functions */
 int QUEUE_NUMS ; 
 int /*<<< orphan*/  dma_free_coherent (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void hix5hd2_destroy_hw_desc_queue(struct hix5hd2_priv *priv)
{
	int i;

	for (i = 0; i < QUEUE_NUMS; i++) {
		if (priv->pool[i].desc) {
			dma_free_coherent(priv->dev, priv->pool[i].size,
					  priv->pool[i].desc,
					  priv->pool[i].phys_addr);
			priv->pool[i].desc = NULL;
		}
	}
}