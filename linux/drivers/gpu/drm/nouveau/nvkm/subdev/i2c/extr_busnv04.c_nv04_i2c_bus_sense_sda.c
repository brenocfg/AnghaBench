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
struct nvkm_i2c_bus {int dummy; } ;
struct nvkm_device {int dummy; } ;
struct TYPE_8__ {TYPE_3__* pad; } ;
struct nv04_i2c_bus {int /*<<< orphan*/  sense; TYPE_4__ base; } ;
struct TYPE_7__ {TYPE_2__* i2c; } ;
struct TYPE_5__ {struct nvkm_device* device; } ;
struct TYPE_6__ {TYPE_1__ subdev; } ;

/* Variables and functions */
 struct nv04_i2c_bus* nv04_i2c_bus (struct nvkm_i2c_bus*) ; 
 int nvkm_rdvgac (struct nvkm_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
nv04_i2c_bus_sense_sda(struct nvkm_i2c_bus *base)
{
	struct nv04_i2c_bus *bus = nv04_i2c_bus(base);
	struct nvkm_device *device = bus->base.pad->i2c->subdev.device;
	return !!(nvkm_rdvgac(device, 0, bus->sense) & 0x08);
}