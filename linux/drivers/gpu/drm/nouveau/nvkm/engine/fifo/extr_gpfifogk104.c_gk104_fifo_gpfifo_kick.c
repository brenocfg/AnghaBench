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
struct TYPE_8__ {TYPE_3__* fifo; } ;
struct gk104_fifo_chan {TYPE_4__ base; } ;
struct TYPE_5__ {int /*<<< orphan*/  mutex; } ;
struct TYPE_6__ {TYPE_1__ subdev; } ;
struct TYPE_7__ {TYPE_2__ engine; } ;

/* Variables and functions */
 int gk104_fifo_gpfifo_kick_locked (struct gk104_fifo_chan*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

int
gk104_fifo_gpfifo_kick(struct gk104_fifo_chan *chan)
{
	int ret;
	mutex_lock(&chan->base.fifo->engine.subdev.mutex);
	ret = gk104_fifo_gpfifo_kick_locked(chan);
	mutex_unlock(&chan->base.fifo->engine.subdev.mutex);
	return ret;
}