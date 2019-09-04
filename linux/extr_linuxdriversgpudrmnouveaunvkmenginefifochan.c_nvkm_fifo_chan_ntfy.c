#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct nvkm_object {int dummy; } ;
struct nvkm_fifo_chan {TYPE_1__* func; } ;
struct nvkm_event {int dummy; } ;
struct TYPE_2__ {int (* ntfy ) (struct nvkm_fifo_chan*,int /*<<< orphan*/ ,struct nvkm_event**) ;} ;

/* Variables and functions */
 int ENODEV ; 
 struct nvkm_fifo_chan* nvkm_fifo_chan (struct nvkm_object*) ; 
 int stub1 (struct nvkm_fifo_chan*,int /*<<< orphan*/ ,struct nvkm_event**) ; 

__attribute__((used)) static int
nvkm_fifo_chan_ntfy(struct nvkm_object *object, u32 type,
		    struct nvkm_event **pevent)
{
	struct nvkm_fifo_chan *chan = nvkm_fifo_chan(object);
	if (chan->func->ntfy)
		return chan->func->ntfy(chan, type, pevent);
	return -ENODEV;
}