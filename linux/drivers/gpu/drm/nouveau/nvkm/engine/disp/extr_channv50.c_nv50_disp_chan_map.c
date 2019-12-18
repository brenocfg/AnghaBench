#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u64 ;
typedef  int /*<<< orphan*/  u32 ;
struct nvkm_object {int dummy; } ;
struct nvkm_device {TYPE_6__* func; } ;
struct nv50_disp_chan {TYPE_1__* func; TYPE_5__* disp; } ;
typedef  enum nvkm_object_map { ____Placeholder_nvkm_object_map } nvkm_object_map ;
struct TYPE_12__ {scalar_t__ (* resource_addr ) (struct nvkm_device*,int /*<<< orphan*/ ) ;} ;
struct TYPE_8__ {struct nvkm_device* device; } ;
struct TYPE_9__ {TYPE_2__ subdev; } ;
struct TYPE_10__ {TYPE_3__ engine; } ;
struct TYPE_11__ {TYPE_4__ base; } ;
struct TYPE_7__ {scalar_t__ const (* user ) (struct nv50_disp_chan*,scalar_t__*) ;} ;

/* Variables and functions */
 int NVKM_OBJECT_MAP_IO ; 
 struct nv50_disp_chan* nv50_disp_chan (struct nvkm_object*) ; 
 scalar_t__ stub1 (struct nvkm_device*,int /*<<< orphan*/ ) ; 
 scalar_t__ const stub2 (struct nv50_disp_chan*,scalar_t__*) ; 

__attribute__((used)) static int
nv50_disp_chan_map(struct nvkm_object *object, void *argv, u32 argc,
		   enum nvkm_object_map *type, u64 *addr, u64 *size)
{
	struct nv50_disp_chan *chan = nv50_disp_chan(object);
	struct nvkm_device *device = chan->disp->base.engine.subdev.device;
	const u64 base = device->func->resource_addr(device, 0);
	*type = NVKM_OBJECT_MAP_IO;
	*addr = base + chan->func->user(chan, size);
	return 0;
}