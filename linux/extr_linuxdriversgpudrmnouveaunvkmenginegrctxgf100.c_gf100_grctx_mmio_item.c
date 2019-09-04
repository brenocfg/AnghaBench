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
typedef  int u32 ;
struct nvkm_device {int dummy; } ;
struct gf100_grctx {int* buffer; TYPE_5__* mmio; scalar_t__ data; TYPE_4__* gr; } ;
struct TYPE_10__ {int addr; int data; int shift; int buffer; } ;
struct TYPE_6__ {struct nvkm_device* device; } ;
struct TYPE_7__ {TYPE_1__ subdev; } ;
struct TYPE_8__ {TYPE_2__ engine; } ;
struct TYPE_9__ {TYPE_3__ base; } ;

/* Variables and functions */
 int /*<<< orphan*/  nvkm_wr32 (struct nvkm_device*,int,int) ; 

void
gf100_grctx_mmio_item(struct gf100_grctx *info, u32 addr, u32 data,
		      int shift, int buffer)
{
	struct nvkm_device *device = info->gr->base.engine.subdev.device;
	if (info->data) {
		if (shift >= 0) {
			info->mmio->addr = addr;
			info->mmio->data = data;
			info->mmio->shift = shift;
			info->mmio->buffer = buffer;
			if (buffer >= 0)
				data |= info->buffer[buffer] >> shift;
			info->mmio++;
		} else
			return;
	} else {
		if (buffer >= 0)
			return;
	}

	nvkm_wr32(device, addr, data);
}