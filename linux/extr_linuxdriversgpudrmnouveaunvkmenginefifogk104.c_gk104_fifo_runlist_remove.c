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
struct nvkm_fifo_cgrp {int /*<<< orphan*/  head; int /*<<< orphan*/  chan_nr; } ;
struct gk104_fifo_chan {int /*<<< orphan*/  head; struct nvkm_fifo_cgrp* cgrp; } ;
struct TYPE_4__ {int /*<<< orphan*/  mutex; } ;
struct TYPE_5__ {TYPE_1__ subdev; } ;
struct TYPE_6__ {TYPE_2__ engine; } ;
struct gk104_fifo {TYPE_3__ base; } ;

/* Variables and functions */
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

void
gk104_fifo_runlist_remove(struct gk104_fifo *fifo, struct gk104_fifo_chan *chan)
{
	struct nvkm_fifo_cgrp *cgrp = chan->cgrp;
	mutex_lock(&fifo->base.engine.subdev.mutex);
	if (!list_empty(&chan->head)) {
		list_del_init(&chan->head);
		if (cgrp && !--cgrp->chan_nr)
			list_del_init(&cgrp->head);
	}
	mutex_unlock(&fifo->base.engine.subdev.mutex);
}