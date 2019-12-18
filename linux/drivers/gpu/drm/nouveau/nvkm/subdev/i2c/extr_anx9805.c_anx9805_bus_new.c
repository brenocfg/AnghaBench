#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct nvkm_i2c_pad {int dummy; } ;
struct nvkm_i2c_bus {int dummy; } ;
struct anx9805_pad {int addr; int /*<<< orphan*/  base; } ;
struct anx9805_bus {int addr; struct nvkm_i2c_bus base; struct anx9805_pad* pad; } ;

/* Variables and functions */
 int ENOMEM ; 
 int ENOSYS ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  anx9805_bus_func ; 
 struct anx9805_pad* anx9805_pad (struct nvkm_i2c_pad*) ; 
 struct anx9805_bus* kzalloc (int,int /*<<< orphan*/ ) ; 
 int nvkm_i2c_bus_ctor (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,struct nvkm_i2c_bus*) ; 

__attribute__((used)) static int
anx9805_bus_new(struct nvkm_i2c_pad *base, int id, u8 drive,
		struct nvkm_i2c_bus **pbus)
{
	struct anx9805_pad *pad = anx9805_pad(base);
	struct anx9805_bus *bus;
	int ret;

	if (!(bus = kzalloc(sizeof(*bus), GFP_KERNEL)))
		return -ENOMEM;
	*pbus = &bus->base;
	bus->pad = pad;

	ret = nvkm_i2c_bus_ctor(&anx9805_bus_func, &pad->base, id, &bus->base);
	if (ret)
		return ret;

	switch (pad->addr) {
	case 0x39: bus->addr = 0x3d; break;
	case 0x3b: bus->addr = 0x3f; break;
	default:
		return -ENOSYS;
	}

	return 0;
}