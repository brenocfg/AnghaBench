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
typedef  int u8 ;
typedef  scalar_t__ u16 ;
struct nvkm_mxm {int /*<<< orphan*/  action; int /*<<< orphan*/  subdev; } ;
struct nvkm_device {int /*<<< orphan*/  cfgopt; struct nvkm_bios* bios; } ;
struct nvkm_bios {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  MXM_SANITISE_DCB ; 
 struct nvkm_mxm* kzalloc (int,int /*<<< orphan*/ ) ; 
 scalar_t__ mxm_shadow (struct nvkm_mxm*,int) ; 
 scalar_t__ mxm_table (struct nvkm_bios*,int*,int*) ; 
 int /*<<< orphan*/  mxms_foreach (struct nvkm_mxm*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int mxms_version (struct nvkm_mxm*) ; 
 int nvbios_rd08 (struct nvkm_bios*,scalar_t__) ; 
 scalar_t__ nvkm_boolopt (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  nvkm_debug (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  nvkm_info (int /*<<< orphan*/ *,char*,int,int) ; 
 int /*<<< orphan*/  nvkm_mxm ; 
 int /*<<< orphan*/  nvkm_subdev_ctor (int /*<<< orphan*/ *,struct nvkm_device*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nvkm_warn (int /*<<< orphan*/ *,char*) ; 

int
nvkm_mxm_new_(struct nvkm_device *device, int index, struct nvkm_mxm **pmxm)
{
	struct nvkm_bios *bios = device->bios;
	struct nvkm_mxm *mxm;
	u8  ver, len;
	u16 data;

	if (!(mxm = *pmxm = kzalloc(sizeof(*mxm), GFP_KERNEL)))
		return -ENOMEM;

	nvkm_subdev_ctor(&nvkm_mxm, device, index, &mxm->subdev);

	data = mxm_table(bios, &ver, &len);
	if (!data || !(ver = nvbios_rd08(bios, data))) {
		nvkm_debug(&mxm->subdev, "no VBIOS data, nothing to do\n");
		return 0;
	}

	nvkm_info(&mxm->subdev, "BIOS version %d.%d\n", ver >> 4, ver & 0x0f);
	nvkm_debug(&mxm->subdev, "module flags: %02x\n",
		   nvbios_rd08(bios, data + 0x01));
	nvkm_debug(&mxm->subdev, "config flags: %02x\n",
		   nvbios_rd08(bios, data + 0x02));

	if (mxm_shadow(mxm, ver)) {
		nvkm_warn(&mxm->subdev, "failed to locate valid SIS\n");
#if 0
		/* we should, perhaps, fall back to some kind of limited
		 * mode here if the x86 vbios hasn't already done the
		 * work for us (so we prevent loading with completely
		 * whacked vbios tables).
		 */
		return -EINVAL;
#else
		return 0;
#endif
	}

	nvkm_debug(&mxm->subdev, "MXMS Version %d.%d\n",
		   mxms_version(mxm) >> 8, mxms_version(mxm) & 0xff);
	mxms_foreach(mxm, 0, NULL, NULL);

	if (nvkm_boolopt(device->cfgopt, "NvMXMDCB", true))
		mxm->action |= MXM_SANITISE_DCB;
	return 0;
}