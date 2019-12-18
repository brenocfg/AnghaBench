#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u64 ;
typedef  int /*<<< orphan*/  u32 ;
struct nvkm_object {int dummy; } ;
struct nvkm_device {int dummy; } ;
struct nv50_disp_chan {TYPE_5__* func; TYPE_4__* disp; } ;
struct TYPE_10__ {scalar_t__ (* user ) (struct nv50_disp_chan*,scalar_t__*) ;} ;
struct TYPE_6__ {struct nvkm_device* device; } ;
struct TYPE_7__ {TYPE_1__ subdev; } ;
struct TYPE_8__ {TYPE_2__ engine; } ;
struct TYPE_9__ {TYPE_3__ base; } ;

/* Variables and functions */
 struct nv50_disp_chan* nv50_disp_chan (struct nvkm_object*) ; 
 int /*<<< orphan*/  nvkm_wr32 (struct nvkm_device*,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ stub1 (struct nv50_disp_chan*,scalar_t__*) ; 

__attribute__((used)) static int
nv50_disp_chan_wr32(struct nvkm_object *object, u64 addr, u32 data)
{
	struct nv50_disp_chan *chan = nv50_disp_chan(object);
	struct nvkm_device *device = chan->disp->base.engine.subdev.device;
	u64 size, base = chan->func->user(chan, &size);
	nvkm_wr32(device, base + addr, data);
	return 0;
}