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
typedef  int u32 ;
struct nvkm_subdev {struct nvkm_device* device; } ;
struct nvkm_engine {int dummy; } ;
struct nvkm_device {int dummy; } ;
struct TYPE_8__ {int tsg; int id; } ;
struct gk104_fifo_engine_status {int busy; int faulted; int chsw; int save; int load; TYPE_4__ next; TYPE_4__* chan; TYPE_4__ prev; } ;
struct TYPE_6__ {struct nvkm_subdev subdev; } ;
struct TYPE_7__ {TYPE_2__ engine; } ;
struct gk104_fifo {TYPE_3__ base; TYPE_1__* engine; } ;
struct TYPE_5__ {struct nvkm_engine* engine; } ;

/* Variables and functions */
 int /*<<< orphan*/  nvkm_debug (struct nvkm_subdev*,char*,int,int,int,int,int,int,char*,int,char*,char*,int,char*) ; 
 scalar_t__ nvkm_engine_chsw_load (struct nvkm_engine*) ; 
 int nvkm_rd32 (struct nvkm_device*,int) ; 

__attribute__((used)) static void
gk104_fifo_engine_status(struct gk104_fifo *fifo, int engn,
			 struct gk104_fifo_engine_status *status)
{
	struct nvkm_engine *engine = fifo->engine[engn].engine;
	struct nvkm_subdev *subdev = &fifo->base.engine.subdev;
	struct nvkm_device *device = subdev->device;
	u32 stat = nvkm_rd32(device, 0x002640 + (engn * 0x08));

	status->busy     = !!(stat & 0x80000000);
	status->faulted  = !!(stat & 0x40000000);
	status->next.tsg = !!(stat & 0x10000000);
	status->next.id  =   (stat & 0x0fff0000) >> 16;
	status->chsw     = !!(stat & 0x00008000);
	status->save     = !!(stat & 0x00004000);
	status->load     = !!(stat & 0x00002000);
	status->prev.tsg = !!(stat & 0x00001000);
	status->prev.id  =   (stat & 0x00000fff);
	status->chan     = NULL;

	if (status->busy && status->chsw) {
		if (status->load && status->save) {
			if (engine && nvkm_engine_chsw_load(engine))
				status->chan = &status->next;
			else
				status->chan = &status->prev;
		} else
		if (status->load) {
			status->chan = &status->next;
		} else {
			status->chan = &status->prev;
		}
	} else
	if (status->load) {
		status->chan = &status->prev;
	}

	nvkm_debug(subdev, "engine %02d: busy %d faulted %d chsw %d "
			   "save %d load %d %sid %d%s-> %sid %d%s\n",
		   engn, status->busy, status->faulted,
		   status->chsw, status->save, status->load,
		   status->prev.tsg ? "tsg" : "ch", status->prev.id,
		   status->chan == &status->prev ? "*" : " ",
		   status->next.tsg ? "tsg" : "ch", status->next.id,
		   status->chan == &status->next ? "*" : " ");
}