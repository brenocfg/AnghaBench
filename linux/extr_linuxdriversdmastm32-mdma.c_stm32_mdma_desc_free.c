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
struct TYPE_3__ {int /*<<< orphan*/  chan; } ;
struct virt_dma_desc {TYPE_1__ tx; } ;
struct stm32_mdma_desc {int count; TYPE_2__* node; } ;
struct stm32_mdma_chan {int /*<<< orphan*/  desc_pool; } ;
struct TYPE_4__ {int /*<<< orphan*/  hwdesc_phys; int /*<<< orphan*/  hwdesc; } ;

/* Variables and functions */
 int /*<<< orphan*/  dma_pool_free (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct stm32_mdma_desc*) ; 
 struct stm32_mdma_chan* to_stm32_mdma_chan (int /*<<< orphan*/ ) ; 
 struct stm32_mdma_desc* to_stm32_mdma_desc (struct virt_dma_desc*) ; 

__attribute__((used)) static void stm32_mdma_desc_free(struct virt_dma_desc *vdesc)
{
	struct stm32_mdma_desc *desc = to_stm32_mdma_desc(vdesc);
	struct stm32_mdma_chan *chan = to_stm32_mdma_chan(vdesc->tx.chan);
	int i;

	for (i = 0; i < desc->count; i++)
		dma_pool_free(chan->desc_pool, desc->node[i].hwdesc,
			      desc->node[i].hwdesc_phys);
	kfree(desc);
}