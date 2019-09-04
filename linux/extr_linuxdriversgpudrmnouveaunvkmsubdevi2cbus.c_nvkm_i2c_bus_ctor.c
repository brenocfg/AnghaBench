#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct nvkm_i2c_pad {TYPE_2__* i2c; } ;
struct nvkm_i2c_bus_func {scalar_t__ drive_scl; } ;
struct TYPE_8__ {int /*<<< orphan*/  parent; } ;
struct TYPE_9__ {int /*<<< orphan*/ * algo; struct i2c_algo_bit_data* algo_data; TYPE_3__ dev; int /*<<< orphan*/  owner; int /*<<< orphan*/  name; } ;
struct nvkm_i2c_bus {int id; TYPE_4__ i2c; struct nvkm_i2c_bus_func const* func; int /*<<< orphan*/  head; int /*<<< orphan*/  mutex; struct nvkm_i2c_pad* pad; } ;
struct nvkm_device {int /*<<< orphan*/  cfgopt; int /*<<< orphan*/  dev; } ;
struct i2c_algo_bit_data {int udelay; int /*<<< orphan*/  getsda; int /*<<< orphan*/  getscl; int /*<<< orphan*/  setsda; int /*<<< orphan*/  setscl; int /*<<< orphan*/  post_xfer; int /*<<< orphan*/  pre_xfer; struct nvkm_i2c_bus* data; int /*<<< orphan*/  timeout; } ;
struct TYPE_6__ {struct nvkm_device* device; } ;
struct TYPE_7__ {int /*<<< orphan*/  bus; TYPE_1__ subdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUS_TRACE (struct nvkm_i2c_bus*,char*) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 char* dev_name (int /*<<< orphan*/ ) ; 
 int i2c_add_adapter (TYPE_4__*) ; 
 int i2c_bit_add_bus (TYPE_4__*) ; 
 struct i2c_algo_bit_data* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nvkm_boolopt (int /*<<< orphan*/ ,char*,int const) ; 
 int /*<<< orphan*/  nvkm_i2c_bus_algo ; 
 int /*<<< orphan*/  nvkm_i2c_bus_getscl ; 
 int /*<<< orphan*/  nvkm_i2c_bus_getsda ; 
 int /*<<< orphan*/  nvkm_i2c_bus_post_xfer ; 
 int /*<<< orphan*/  nvkm_i2c_bus_pre_xfer ; 
 int /*<<< orphan*/  nvkm_i2c_bus_setscl ; 
 int /*<<< orphan*/  nvkm_i2c_bus_setsda ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int,char*,char*,int) ; 
 int /*<<< orphan*/  usecs_to_jiffies (int) ; 

int
nvkm_i2c_bus_ctor(const struct nvkm_i2c_bus_func *func,
		  struct nvkm_i2c_pad *pad, int id,
		  struct nvkm_i2c_bus *bus)
{
	struct nvkm_device *device = pad->i2c->subdev.device;
	struct i2c_algo_bit_data *bit;
#ifndef CONFIG_NOUVEAU_I2C_INTERNAL_DEFAULT
	const bool internal = false;
#else
	const bool internal = true;
#endif
	int ret;

	bus->func = func;
	bus->pad = pad;
	bus->id = id;
	mutex_init(&bus->mutex);
	list_add_tail(&bus->head, &pad->i2c->bus);
	BUS_TRACE(bus, "ctor");

	snprintf(bus->i2c.name, sizeof(bus->i2c.name), "nvkm-%s-bus-%04x",
		 dev_name(device->dev), id);
	bus->i2c.owner = THIS_MODULE;
	bus->i2c.dev.parent = device->dev;

	if ( bus->func->drive_scl &&
	    !nvkm_boolopt(device->cfgopt, "NvI2C", internal)) {
		if (!(bit = kzalloc(sizeof(*bit), GFP_KERNEL)))
			return -ENOMEM;
		bit->udelay = 10;
		bit->timeout = usecs_to_jiffies(2200);
		bit->data = bus;
		bit->pre_xfer = nvkm_i2c_bus_pre_xfer;
		bit->post_xfer = nvkm_i2c_bus_post_xfer;
		bit->setscl = nvkm_i2c_bus_setscl;
		bit->setsda = nvkm_i2c_bus_setsda;
		bit->getscl = nvkm_i2c_bus_getscl;
		bit->getsda = nvkm_i2c_bus_getsda;
		bus->i2c.algo_data = bit;
		ret = i2c_bit_add_bus(&bus->i2c);
	} else {
		bus->i2c.algo = &nvkm_i2c_bus_algo;
		ret = i2c_add_adapter(&bus->i2c);
	}

	return ret;
}