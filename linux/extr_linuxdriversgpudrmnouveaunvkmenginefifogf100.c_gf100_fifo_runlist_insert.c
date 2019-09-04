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
struct gf100_fifo_chan {int /*<<< orphan*/  head; } ;
struct TYPE_4__ {int /*<<< orphan*/  mutex; } ;
struct TYPE_5__ {TYPE_1__ subdev; } ;
struct TYPE_6__ {TYPE_2__ engine; } ;
struct gf100_fifo {TYPE_3__ base; int /*<<< orphan*/  chan; } ;

/* Variables and functions */
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

void
gf100_fifo_runlist_insert(struct gf100_fifo *fifo, struct gf100_fifo_chan *chan)
{
	mutex_lock(&fifo->base.engine.subdev.mutex);
	list_add_tail(&chan->head, &fifo->chan);
	mutex_unlock(&fifo->base.engine.subdev.mutex);
}