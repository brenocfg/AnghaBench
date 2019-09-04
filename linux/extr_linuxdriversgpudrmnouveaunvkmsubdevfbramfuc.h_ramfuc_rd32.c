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
typedef  int /*<<< orphan*/  u32 ;
struct ramfuc_reg {scalar_t__ sequence; int /*<<< orphan*/  data; int /*<<< orphan*/  addr; } ;
struct ramfuc {scalar_t__ sequence; TYPE_2__* fb; } ;
struct nvkm_device {int dummy; } ;
struct TYPE_3__ {struct nvkm_device* device; } ;
struct TYPE_4__ {TYPE_1__ subdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  nvkm_rd32 (struct nvkm_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline u32
ramfuc_rd32(struct ramfuc *ram, struct ramfuc_reg *reg)
{
	struct nvkm_device *device = ram->fb->subdev.device;
	if (reg->sequence != ram->sequence)
		reg->data = nvkm_rd32(device, reg->addr);
	return reg->data;
}