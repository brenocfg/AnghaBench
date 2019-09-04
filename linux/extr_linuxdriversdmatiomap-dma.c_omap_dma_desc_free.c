#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {TYPE_2__* chan; } ;
struct virt_dma_desc {TYPE_3__ tx; } ;
struct omap_dmadev {int /*<<< orphan*/  desc_pool; } ;
struct omap_desc {int sglen; TYPE_1__* sg; scalar_t__ using_ll; } ;
struct TYPE_5__ {int /*<<< orphan*/  device; } ;
struct TYPE_4__ {int /*<<< orphan*/  t2_desc_paddr; scalar_t__ t2_desc; } ;

/* Variables and functions */
 int /*<<< orphan*/  dma_pool_free (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct omap_desc*) ; 
 struct omap_desc* to_omap_dma_desc (TYPE_3__*) ; 
 struct omap_dmadev* to_omap_dma_dev (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void omap_dma_desc_free(struct virt_dma_desc *vd)
{
	struct omap_desc *d = to_omap_dma_desc(&vd->tx);

	if (d->using_ll) {
		struct omap_dmadev *od = to_omap_dma_dev(vd->tx.chan->device);
		int i;

		for (i = 0; i < d->sglen; i++) {
			if (d->sg[i].t2_desc)
				dma_pool_free(od->desc_pool, d->sg[i].t2_desc,
					      d->sg[i].t2_desc_paddr);
		}
	}

	kfree(d);
}