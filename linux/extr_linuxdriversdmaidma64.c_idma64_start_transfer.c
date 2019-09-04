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
struct virt_dma_desc {int /*<<< orphan*/  node; } ;
struct TYPE_3__ {int /*<<< orphan*/  device; } ;
struct TYPE_4__ {TYPE_1__ chan; } ;
struct idma64_chan {int /*<<< orphan*/ * desc; TYPE_2__ vchan; } ;
struct idma64 {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  idma64_chan_init (struct idma64*,struct idma64_chan*) ; 
 int /*<<< orphan*/  idma64_chan_start (struct idma64*,struct idma64_chan*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 struct idma64* to_idma64 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * to_idma64_desc (struct virt_dma_desc*) ; 
 struct virt_dma_desc* vchan_next_desc (TYPE_2__*) ; 

__attribute__((used)) static void idma64_start_transfer(struct idma64_chan *idma64c)
{
	struct idma64 *idma64 = to_idma64(idma64c->vchan.chan.device);
	struct virt_dma_desc *vdesc;

	/* Get the next descriptor */
	vdesc = vchan_next_desc(&idma64c->vchan);
	if (!vdesc) {
		idma64c->desc = NULL;
		return;
	}

	list_del(&vdesc->node);
	idma64c->desc = to_idma64_desc(vdesc);

	/* Configure the channel */
	idma64_chan_init(idma64, idma64c);

	/* Start the channel with a new descriptor */
	idma64_chan_start(idma64, idma64c);
}