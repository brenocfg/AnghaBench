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
struct nv50_dmac {int /*<<< orphan*/  push; int /*<<< orphan*/  base; int /*<<< orphan*/  sync; int /*<<< orphan*/  vram; } ;

/* Variables and functions */
 int /*<<< orphan*/  nv50_chan_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nvif_mem_fini (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nvif_object_fini (int /*<<< orphan*/ *) ; 

void
nv50_dmac_destroy(struct nv50_dmac *dmac)
{
	nvif_object_fini(&dmac->vram);
	nvif_object_fini(&dmac->sync);

	nv50_chan_destroy(&dmac->base);

	nvif_mem_fini(&dmac->push);
}