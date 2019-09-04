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
typedef  size_t u8 ;
typedef  int u32 ;
struct nvkm_i2c_pad {TYPE_1__* i2c; } ;
struct nvkm_i2c_bus {int dummy; } ;
struct nv50_i2c_bus {int addr; int data; struct nvkm_i2c_bus base; } ;
struct TYPE_2__ {int /*<<< orphan*/  subdev; } ;

/* Variables and functions */
 size_t ARRAY_SIZE (int const*) ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct nv50_i2c_bus* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nv50_i2c_bus_func ; 
 int /*<<< orphan*/  nvkm_i2c_bus_ctor (int /*<<< orphan*/ *,struct nvkm_i2c_pad*,int,struct nvkm_i2c_bus*) ; 
 int /*<<< orphan*/  nvkm_warn (int /*<<< orphan*/ *,char*,size_t) ; 

int
nv50_i2c_bus_new(struct nvkm_i2c_pad *pad, int id, u8 drive,
		 struct nvkm_i2c_bus **pbus)
{
	static const u32 addr[] = {
		0x00e138, 0x00e150, 0x00e168, 0x00e180,
		0x00e254, 0x00e274, 0x00e764, 0x00e780,
		0x00e79c, 0x00e7b8
	};
	struct nv50_i2c_bus *bus;

	if (drive >= ARRAY_SIZE(addr)) {
		nvkm_warn(&pad->i2c->subdev, "bus %d unknown\n", drive);
		return -ENODEV;
	}

	if (!(bus = kzalloc(sizeof(*bus), GFP_KERNEL)))
		return -ENOMEM;
	*pbus = &bus->base;

	nvkm_i2c_bus_ctor(&nv50_i2c_bus_func, pad, id, &bus->base);
	bus->addr = addr[drive];
	bus->data = 0x00000007;
	return 0;
}