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
struct netsec_priv {int /*<<< orphan*/  dev; struct netsec_desc_ring* desc_ring; } ;
struct netsec_desc_ring {int /*<<< orphan*/ * desc; int /*<<< orphan*/ * vaddr; int /*<<< orphan*/  desc_dma; } ;

/* Variables and functions */
 int DESC_NUM ; 
 int DESC_SZ ; 
 int /*<<< orphan*/  dma_free_coherent (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void netsec_free_dring(struct netsec_priv *priv, int id)
{
	struct netsec_desc_ring *dring = &priv->desc_ring[id];

	if (dring->vaddr) {
		dma_free_coherent(priv->dev, DESC_SZ * DESC_NUM,
				  dring->vaddr, dring->desc_dma);
		dring->vaddr = NULL;
	}

	kfree(dring->desc);
	dring->desc = NULL;
}