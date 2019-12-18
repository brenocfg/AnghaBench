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
struct nvkm_subdev {struct nvkm_device* device; } ;
struct nvkm_device {int chipset; int /*<<< orphan*/  dev; } ;
struct gf100_gr_fuc {int /*<<< orphan*/ * data; int /*<<< orphan*/  size; } ;
struct TYPE_3__ {struct nvkm_subdev subdev; } ;
struct TYPE_4__ {TYPE_1__ engine; } ;
struct gf100_gr {TYPE_2__ base; } ;
struct firmware {int /*<<< orphan*/  data; int /*<<< orphan*/  size; } ;
typedef  int /*<<< orphan*/  f ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/ * kmemdup (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nvkm_debug (struct nvkm_subdev*,char*,char const*) ; 
 int /*<<< orphan*/  nvkm_error (struct nvkm_subdev*,char*,char const*) ; 
 int /*<<< orphan*/  release_firmware (struct firmware const*) ; 
 int request_firmware (struct firmware const**,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,...) ; 
 int /*<<< orphan*/  strcmp (char const*,char*) ; 

int
gf100_gr_ctor_fw_legacy(struct gf100_gr *gr, const char *fwname,
			struct gf100_gr_fuc *fuc, int ret)
{
	struct nvkm_subdev *subdev = &gr->base.engine.subdev;
	struct nvkm_device *device = subdev->device;
	const struct firmware *fw;
	char f[32];

	/* see if this firmware has a legacy path */
	if (!strcmp(fwname, "fecs_inst"))
		fwname = "fuc409c";
	else if (!strcmp(fwname, "fecs_data"))
		fwname = "fuc409d";
	else if (!strcmp(fwname, "gpccs_inst"))
		fwname = "fuc41ac";
	else if (!strcmp(fwname, "gpccs_data"))
		fwname = "fuc41ad";
	else {
		/* nope, let's just return the error we got */
		nvkm_error(subdev, "failed to load %s\n", fwname);
		return ret;
	}

	/* yes, try to load from the legacy path */
	nvkm_debug(subdev, "%s: falling back to legacy path\n", fwname);

	snprintf(f, sizeof(f), "nouveau/nv%02x_%s", device->chipset, fwname);
	ret = request_firmware(&fw, f, device->dev);
	if (ret) {
		snprintf(f, sizeof(f), "nouveau/%s", fwname);
		ret = request_firmware(&fw, f, device->dev);
		if (ret) {
			nvkm_error(subdev, "failed to load %s\n", fwname);
			return ret;
		}
	}

	fuc->size = fw->size;
	fuc->data = kmemdup(fw->data, fuc->size, GFP_KERNEL);
	release_firmware(fw);
	return (fuc->data != NULL) ? 0 : -ENOMEM;
}