#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct nvkm_fifo_cgrp {int /*<<< orphan*/  chan; int /*<<< orphan*/  head; int /*<<< orphan*/  chan_nr; } ;
struct gk104_fifo_chan {size_t runl; int /*<<< orphan*/  head; struct nvkm_fifo_cgrp* cgrp; } ;
struct TYPE_6__ {int /*<<< orphan*/  mutex; } ;
struct TYPE_7__ {TYPE_2__ subdev; } ;
struct TYPE_8__ {TYPE_3__ engine; } ;
struct gk104_fifo {TYPE_4__ base; TYPE_1__* runlist; } ;
struct TYPE_5__ {int /*<<< orphan*/  chan; int /*<<< orphan*/  cgrp; } ;

/* Variables and functions */
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

void
gk104_fifo_runlist_insert(struct gk104_fifo *fifo, struct gk104_fifo_chan *chan)
{
	struct nvkm_fifo_cgrp *cgrp = chan->cgrp;
	mutex_lock(&fifo->base.engine.subdev.mutex);
	if (cgrp) {
		if (!cgrp->chan_nr++)
			list_add_tail(&cgrp->head, &fifo->runlist[chan->runl].cgrp);
		list_add_tail(&chan->head, &cgrp->chan);
	} else {
		list_add_tail(&chan->head, &fifo->runlist[chan->runl].chan);
	}
	mutex_unlock(&fifo->base.engine.subdev.mutex);
}