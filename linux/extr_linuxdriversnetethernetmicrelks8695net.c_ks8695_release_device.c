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
struct ks8695_priv {int /*<<< orphan*/  ring_base_dma; int /*<<< orphan*/  ring_base; int /*<<< orphan*/  dev; scalar_t__ phyiface_req; scalar_t__ regs_req; scalar_t__ phyiface_regs; scalar_t__ io_regs; } ;

/* Variables and functions */
 int /*<<< orphan*/  RING_DMA_SIZE ; 
 int /*<<< orphan*/  dma_free_coherent (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iounmap (scalar_t__) ; 
 int /*<<< orphan*/  kfree (scalar_t__) ; 
 int /*<<< orphan*/  release_resource (scalar_t__) ; 

__attribute__((used)) static void
ks8695_release_device(struct ks8695_priv *ksp)
{
	/* Unmap the registers */
	iounmap(ksp->io_regs);
	if (ksp->phyiface_regs)
		iounmap(ksp->phyiface_regs);

	/* And release the request */
	release_resource(ksp->regs_req);
	kfree(ksp->regs_req);
	if (ksp->phyiface_req) {
		release_resource(ksp->phyiface_req);
		kfree(ksp->phyiface_req);
	}

	/* Free the ring buffers */
	dma_free_coherent(ksp->dev, RING_DMA_SIZE,
			  ksp->ring_base, ksp->ring_base_dma);
}