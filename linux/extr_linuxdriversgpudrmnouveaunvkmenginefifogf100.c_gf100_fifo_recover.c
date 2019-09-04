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
typedef  int u32 ;
struct nvkm_subdev {size_t index; struct nvkm_device* device; } ;
struct nvkm_engine {struct nvkm_subdev subdev; } ;
struct nvkm_device {int dummy; } ;
struct TYPE_4__ {int chid; } ;
struct gf100_fifo_chan {int killed; int /*<<< orphan*/  head; TYPE_1__ base; } ;
struct TYPE_6__ {struct nvkm_engine engine; int /*<<< orphan*/  lock; } ;
struct TYPE_5__ {unsigned long long mask; int /*<<< orphan*/  work; } ;
struct gf100_fifo {TYPE_3__ base; TYPE_2__ recover; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert_spin_locked (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nvkm_error (struct nvkm_subdev*,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  nvkm_fifo_kevent (TYPE_3__*,int) ; 
 int /*<<< orphan*/  nvkm_mask (struct nvkm_device*,int,int,int) ; 
 int /*<<< orphan*/ * nvkm_subdev_name ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
gf100_fifo_recover(struct gf100_fifo *fifo, struct nvkm_engine *engine,
		   struct gf100_fifo_chan *chan)
{
	struct nvkm_subdev *subdev = &fifo->base.engine.subdev;
	struct nvkm_device *device = subdev->device;
	u32 chid = chan->base.chid;

	nvkm_error(subdev, "%s engine fault on channel %d, recovering...\n",
		   nvkm_subdev_name[engine->subdev.index], chid);
	assert_spin_locked(&fifo->base.lock);

	nvkm_mask(device, 0x003004 + (chid * 0x08), 0x00000001, 0x00000000);
	list_del_init(&chan->head);
	chan->killed = true;

	if (engine != &fifo->base.engine)
		fifo->recover.mask |= 1ULL << engine->subdev.index;
	schedule_work(&fifo->recover.work);
	nvkm_fifo_kevent(&fifo->base, chid);
}