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
struct nvkm_i2c_pad {TYPE_1__* func; } ;
struct nvkm_i2c_func {int (* pad_s_new ) (struct nvkm_i2c*,int const,struct nvkm_i2c_pad**) ;int (* pad_x_new ) (struct nvkm_i2c*,int /*<<< orphan*/ ,struct nvkm_i2c_pad**) ;} ;
struct nvkm_i2c_drv {int (* pad_new ) (struct nvkm_i2c_bus*,int const,int /*<<< orphan*/ ,struct nvkm_i2c_pad**) ;scalar_t__ bios; int /*<<< orphan*/  addr; } ;
struct nvkm_i2c_bus {int dummy; } ;
struct nvkm_i2c_aux {int dummy; } ;
struct nvkm_i2c {int /*<<< orphan*/  event; int /*<<< orphan*/  subdev; int /*<<< orphan*/  aux; int /*<<< orphan*/  bus; int /*<<< orphan*/  pad; struct nvkm_i2c_func const* func; } ;
struct nvkm_device {struct nvkm_bios* bios; } ;
struct nvkm_bios {int dummy; } ;
struct dcb_output {scalar_t__ extdev; scalar_t__ type; int /*<<< orphan*/  i2c_index; int /*<<< orphan*/  location; } ;
struct dcb_i2c_entry {scalar_t__ type; scalar_t__ drive; scalar_t__ share; scalar_t__ auxch; int /*<<< orphan*/  sense; } ;
struct TYPE_2__ {int (* bus_new_0 ) (struct nvkm_i2c_pad*,int const,scalar_t__,int /*<<< orphan*/ ,struct nvkm_i2c_bus**) ;int (* bus_new_4 ) (struct nvkm_i2c_pad*,int const,scalar_t__,struct nvkm_i2c_bus**) ;int (* aux_new_6 ) (struct nvkm_i2c_pad*,int const,scalar_t__,struct nvkm_i2c_aux**) ;} ;

/* Variables and functions */
 scalar_t__ DCB_I2C_NV04_BIT ; 
 scalar_t__ DCB_I2C_NV4E_BIT ; 
 scalar_t__ DCB_I2C_NVIO_AUX ; 
 scalar_t__ DCB_I2C_NVIO_BIT ; 
 scalar_t__ DCB_I2C_PMGR ; 
 scalar_t__ DCB_I2C_UNUSED ; 
 scalar_t__ DCB_OUTPUT_DP ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int NVKM_I2C_AUX_EXT (scalar_t__) ; 
 int const NVKM_I2C_BUS_CCB (int) ; 
 int NVKM_I2C_BUS_EXT (scalar_t__) ; 
 int /*<<< orphan*/  NVKM_I2C_PAD_CCB (int) ; 
 int const NVKM_I2C_PAD_EXT (scalar_t__) ; 
 int NVKM_I2C_PAD_HYBRID (scalar_t__) ; 
 int /*<<< orphan*/  dcb_i2c_parse (struct nvkm_bios*,int,struct dcb_i2c_entry*) ; 
 scalar_t__ dcb_outp_parse (struct nvkm_bios*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct dcb_output*) ; 
 struct nvkm_i2c* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nvkm_debug (int /*<<< orphan*/ *,char*,int,...) ; 
 int /*<<< orphan*/  nvkm_error (int /*<<< orphan*/ *,char*,int,int) ; 
 int nvkm_event_init (int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nvkm_i2c ; 
 int /*<<< orphan*/  nvkm_i2c_aux_del (struct nvkm_i2c_aux**) ; 
 int /*<<< orphan*/  nvkm_i2c_bus_del (struct nvkm_i2c_bus**) ; 
 struct nvkm_i2c_bus* nvkm_i2c_bus_find (struct nvkm_i2c*,int /*<<< orphan*/ ) ; 
 struct nvkm_i2c_drv* nvkm_i2c_drv ; 
 int /*<<< orphan*/  nvkm_i2c_intr_func ; 
 int /*<<< orphan*/  nvkm_i2c_pad_del (struct nvkm_i2c_pad**) ; 
 struct nvkm_i2c_pad* nvkm_i2c_pad_find (struct nvkm_i2c*,int const) ; 
 int /*<<< orphan*/  nvkm_subdev_ctor (int /*<<< orphan*/ *,struct nvkm_device*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nvkm_warn (int /*<<< orphan*/ *,char*,int) ; 
 int stub1 (struct nvkm_i2c*,int const,struct nvkm_i2c_pad**) ; 
 int stub2 (struct nvkm_i2c*,int /*<<< orphan*/ ,struct nvkm_i2c_pad**) ; 
 int stub3 (struct nvkm_i2c_pad*,int const,scalar_t__,int /*<<< orphan*/ ,struct nvkm_i2c_bus**) ; 
 int stub4 (struct nvkm_i2c_pad*,int const,scalar_t__,struct nvkm_i2c_bus**) ; 
 int stub5 (struct nvkm_i2c_pad*,int const,scalar_t__,struct nvkm_i2c_aux**) ; 
 int stub6 (struct nvkm_i2c_bus*,int const,int /*<<< orphan*/ ,struct nvkm_i2c_pad**) ; 
 int stub7 (struct nvkm_i2c_pad*,int const,scalar_t__,struct nvkm_i2c_aux**) ; 
 int stub8 (struct nvkm_i2c_pad*,int const,scalar_t__,struct nvkm_i2c_bus**) ; 

int
nvkm_i2c_new_(const struct nvkm_i2c_func *func, struct nvkm_device *device,
	      int index, struct nvkm_i2c **pi2c)
{
	struct nvkm_bios *bios = device->bios;
	struct nvkm_i2c *i2c;
	struct dcb_i2c_entry ccbE;
	struct dcb_output dcbE;
	u8 ver, hdr;
	int ret, i;

	if (!(i2c = *pi2c = kzalloc(sizeof(*i2c), GFP_KERNEL)))
		return -ENOMEM;

	nvkm_subdev_ctor(&nvkm_i2c, device, index, &i2c->subdev);
	i2c->func = func;
	INIT_LIST_HEAD(&i2c->pad);
	INIT_LIST_HEAD(&i2c->bus);
	INIT_LIST_HEAD(&i2c->aux);

	i = -1;
	while (!dcb_i2c_parse(bios, ++i, &ccbE)) {
		struct nvkm_i2c_pad *pad = NULL;
		struct nvkm_i2c_bus *bus = NULL;
		struct nvkm_i2c_aux *aux = NULL;

		nvkm_debug(&i2c->subdev, "ccb %02x: type %02x drive %02x "
			   "sense %02x share %02x auxch %02x\n", i, ccbE.type,
			   ccbE.drive, ccbE.sense, ccbE.share, ccbE.auxch);

		if (ccbE.share != DCB_I2C_UNUSED) {
			const int id = NVKM_I2C_PAD_HYBRID(ccbE.share);
			if (!(pad = nvkm_i2c_pad_find(i2c, id)))
				ret = func->pad_s_new(i2c, id, &pad);
			else
				ret = 0;
		} else {
			ret = func->pad_x_new(i2c, NVKM_I2C_PAD_CCB(i), &pad);
		}

		if (ret) {
			nvkm_error(&i2c->subdev, "ccb %02x pad, %d\n", i, ret);
			nvkm_i2c_pad_del(&pad);
			continue;
		}

		if (pad->func->bus_new_0 && ccbE.type == DCB_I2C_NV04_BIT) {
			ret = pad->func->bus_new_0(pad, NVKM_I2C_BUS_CCB(i),
						   ccbE.drive,
						   ccbE.sense, &bus);
		} else
		if (pad->func->bus_new_4 &&
		    ( ccbE.type == DCB_I2C_NV4E_BIT ||
		      ccbE.type == DCB_I2C_NVIO_BIT ||
		     (ccbE.type == DCB_I2C_PMGR &&
		      ccbE.drive != DCB_I2C_UNUSED))) {
			ret = pad->func->bus_new_4(pad, NVKM_I2C_BUS_CCB(i),
						   ccbE.drive, &bus);
		}

		if (ret) {
			nvkm_error(&i2c->subdev, "ccb %02x bus, %d\n", i, ret);
			nvkm_i2c_bus_del(&bus);
		}

		if (pad->func->aux_new_6 &&
		    ( ccbE.type == DCB_I2C_NVIO_AUX ||
		     (ccbE.type == DCB_I2C_PMGR &&
		      ccbE.auxch != DCB_I2C_UNUSED))) {
			ret = pad->func->aux_new_6(pad, NVKM_I2C_BUS_CCB(i),
						   ccbE.auxch, &aux);
		} else {
			ret = 0;
		}

		if (ret) {
			nvkm_error(&i2c->subdev, "ccb %02x aux, %d\n", i, ret);
			nvkm_i2c_aux_del(&aux);
		}

		if (ccbE.type != DCB_I2C_UNUSED && !bus && !aux) {
			nvkm_warn(&i2c->subdev, "ccb %02x was ignored\n", i);
			continue;
		}
	}

	i = -1;
	while (dcb_outp_parse(bios, ++i, &ver, &hdr, &dcbE)) {
		const struct nvkm_i2c_drv *drv = nvkm_i2c_drv;
		struct nvkm_i2c_bus *bus;
		struct nvkm_i2c_pad *pad;

		/* internal outputs handled by native i2c busses (above) */
		if (!dcbE.location)
			continue;

		/* we need an i2c bus to talk to the external encoder */
		bus = nvkm_i2c_bus_find(i2c, dcbE.i2c_index);
		if (!bus) {
			nvkm_debug(&i2c->subdev, "dcb %02x no bus\n", i);
			continue;
		}

		/* ... and a driver for it */
		while (drv->pad_new) {
			if (drv->bios == dcbE.extdev)
				break;
			drv++;
		}

		if (!drv->pad_new) {
			nvkm_debug(&i2c->subdev, "dcb %02x drv %02x unknown\n",
				   i, dcbE.extdev);
			continue;
		}

		/* find/create an instance of the driver */
		pad = nvkm_i2c_pad_find(i2c, NVKM_I2C_PAD_EXT(dcbE.extdev));
		if (!pad) {
			const int id = NVKM_I2C_PAD_EXT(dcbE.extdev);
			ret = drv->pad_new(bus, id, drv->addr, &pad);
			if (ret) {
				nvkm_error(&i2c->subdev, "dcb %02x pad, %d\n",
					   i, ret);
				nvkm_i2c_pad_del(&pad);
				continue;
			}
		}

		/* create any i2c bus / aux channel required by the output */
		if (pad->func->aux_new_6 && dcbE.type == DCB_OUTPUT_DP) {
			const int id = NVKM_I2C_AUX_EXT(dcbE.extdev);
			struct nvkm_i2c_aux *aux = NULL;
			ret = pad->func->aux_new_6(pad, id, 0, &aux);
			if (ret) {
				nvkm_error(&i2c->subdev, "dcb %02x aux, %d\n",
					   i, ret);
				nvkm_i2c_aux_del(&aux);
			}
		} else
		if (pad->func->bus_new_4) {
			const int id = NVKM_I2C_BUS_EXT(dcbE.extdev);
			struct nvkm_i2c_bus *bus = NULL;
			ret = pad->func->bus_new_4(pad, id, 0, &bus);
			if (ret) {
				nvkm_error(&i2c->subdev, "dcb %02x bus, %d\n",
					   i, ret);
				nvkm_i2c_bus_del(&bus);
			}
		}
	}

	return nvkm_event_init(&nvkm_i2c_intr_func, 4, i, &i2c->event);
}