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
struct pxa3xx_gcu_priv {struct pxa3xx_gcu_batch* free; } ;
struct pxa3xx_gcu_batch {int /*<<< orphan*/  phys; int /*<<< orphan*/  ptr; struct pxa3xx_gcu_batch* next; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int PXA3XX_GCU_BATCH_WORDS ; 
 int /*<<< orphan*/  dma_free_coherent (struct device*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct pxa3xx_gcu_batch*) ; 

__attribute__((used)) static void
pxa3xx_gcu_free_buffers(struct device *dev,
			struct pxa3xx_gcu_priv *priv)
{
	struct pxa3xx_gcu_batch *next, *buffer = priv->free;

	while (buffer) {
		next = buffer->next;

		dma_free_coherent(dev, PXA3XX_GCU_BATCH_WORDS * 4,
				  buffer->ptr, buffer->phys);

		kfree(buffer);
		buffer = next;
	}

	priv->free = NULL;
}