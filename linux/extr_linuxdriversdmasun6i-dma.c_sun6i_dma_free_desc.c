#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {TYPE_1__* chan; } ;
struct virt_dma_desc {TYPE_2__ tx; } ;
struct sun6i_dma_lli {int /*<<< orphan*/  p_lli_next; struct sun6i_dma_lli* v_lli_next; } ;
struct sun6i_dma_dev {int /*<<< orphan*/  pool; } ;
struct sun6i_desc {struct sun6i_dma_lli* v_lli; int /*<<< orphan*/  p_lli; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;
struct TYPE_3__ {int /*<<< orphan*/  device; } ;

/* Variables and functions */
 int /*<<< orphan*/  dma_pool_free (int /*<<< orphan*/ ,struct sun6i_dma_lli*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct sun6i_desc*) ; 
 struct sun6i_desc* to_sun6i_desc (TYPE_2__*) ; 
 struct sun6i_dma_dev* to_sun6i_dma_dev (int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static void sun6i_dma_free_desc(struct virt_dma_desc *vd)
{
	struct sun6i_desc *txd = to_sun6i_desc(&vd->tx);
	struct sun6i_dma_dev *sdev = to_sun6i_dma_dev(vd->tx.chan->device);
	struct sun6i_dma_lli *v_lli, *v_next;
	dma_addr_t p_lli, p_next;

	if (unlikely(!txd))
		return;

	p_lli = txd->p_lli;
	v_lli = txd->v_lli;

	while (v_lli) {
		v_next = v_lli->v_lli_next;
		p_next = v_lli->p_lli_next;

		dma_pool_free(sdev->pool, v_lli, p_lli);

		v_lli = v_next;
		p_lli = p_next;
	}

	kfree(txd);
}