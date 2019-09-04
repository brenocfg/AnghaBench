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
struct virt_dma_desc {int /*<<< orphan*/  node; } ;
struct hsu_dma_chan {int /*<<< orphan*/ * desc; int /*<<< orphan*/  vchan; } ;

/* Variables and functions */
 int /*<<< orphan*/  hsu_dma_start_channel (struct hsu_dma_chan*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * to_hsu_dma_desc (struct virt_dma_desc*) ; 
 struct virt_dma_desc* vchan_next_desc (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void hsu_dma_start_transfer(struct hsu_dma_chan *hsuc)
{
	struct virt_dma_desc *vdesc;

	/* Get the next descriptor */
	vdesc = vchan_next_desc(&hsuc->vchan);
	if (!vdesc) {
		hsuc->desc = NULL;
		return;
	}

	list_del(&vdesc->node);
	hsuc->desc = to_hsu_dma_desc(vdesc);

	/* Start the channel with a new descriptor */
	hsu_dma_start_channel(hsuc);
}