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
typedef  int /*<<< orphan*/  u8 ;
struct nvkm_i2c_pad {int dummy; } ;
struct nvkm_i2c_bus {TYPE_1__* pad; } ;
struct anx9805_pad {int /*<<< orphan*/  addr; struct nvkm_i2c_bus* bus; struct nvkm_i2c_pad base; } ;
struct TYPE_2__ {int /*<<< orphan*/  i2c; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  anx9805_pad_func ; 
 struct anx9805_pad* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nvkm_i2c_pad_ctor (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,struct nvkm_i2c_pad*) ; 

int
anx9805_pad_new(struct nvkm_i2c_bus *bus, int id, u8 addr,
		struct nvkm_i2c_pad **ppad)
{
	struct anx9805_pad *pad;

	if (!(pad = kzalloc(sizeof(*pad), GFP_KERNEL)))
		return -ENOMEM;
	*ppad = &pad->base;

	nvkm_i2c_pad_ctor(&anx9805_pad_func, bus->pad->i2c, id, &pad->base);
	pad->bus = bus;
	pad->addr = addr;
	return 0;
}