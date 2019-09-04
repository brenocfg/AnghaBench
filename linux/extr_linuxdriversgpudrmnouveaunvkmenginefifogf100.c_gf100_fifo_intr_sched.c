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
typedef  int u32 ;
struct nvkm_subdev {struct nvkm_device* device; } ;
struct nvkm_enum {char* name; } ;
struct nvkm_device {int dummy; } ;
struct TYPE_3__ {struct nvkm_subdev subdev; } ;
struct TYPE_4__ {TYPE_1__ engine; } ;
struct gf100_fifo {TYPE_2__ base; } ;

/* Variables and functions */
 int /*<<< orphan*/  gf100_fifo_intr_sched_ctxsw (struct gf100_fifo*) ; 
 int /*<<< orphan*/  gf100_fifo_sched_reason ; 
 struct nvkm_enum* nvkm_enum_find (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  nvkm_error (struct nvkm_subdev*,char*,int,char*) ; 
 int nvkm_rd32 (struct nvkm_device*,int) ; 

__attribute__((used)) static void
gf100_fifo_intr_sched(struct gf100_fifo *fifo)
{
	struct nvkm_subdev *subdev = &fifo->base.engine.subdev;
	struct nvkm_device *device = subdev->device;
	u32 intr = nvkm_rd32(device, 0x00254c);
	u32 code = intr & 0x000000ff;
	const struct nvkm_enum *en;

	en = nvkm_enum_find(gf100_fifo_sched_reason, code);

	nvkm_error(subdev, "SCHED_ERROR %02x [%s]\n", code, en ? en->name : "");

	switch (code) {
	case 0x0a:
		gf100_fifo_intr_sched_ctxsw(fifo);
		break;
	default:
		break;
	}
}