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
typedef  int u8 ;
typedef  int u16 ;
struct nvkm_subdev {TYPE_1__* device; } ;
struct nvkm_mxm {struct nvkm_subdev subdev; } ;
struct nvkm_bios {int dummy; } ;
struct TYPE_2__ {struct nvkm_bios* bios; } ;

/* Variables and functions */
 int /*<<< orphan*/  dcb_outp_foreach (struct nvkm_bios*,struct nvkm_mxm*,int /*<<< orphan*/ ) ; 
 int dcb_table (struct nvkm_bios*,int*,int*,int*,int*) ; 
 int /*<<< orphan*/  mxm_dcb_sanitise_entry ; 
 int /*<<< orphan*/  mxm_show_unmatched ; 
 int /*<<< orphan*/  mxms_foreach (struct nvkm_mxm*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nvkm_warn (struct nvkm_subdev*,char*) ; 

__attribute__((used)) static void
mxm_dcb_sanitise(struct nvkm_mxm *mxm)
{
	struct nvkm_subdev *subdev = &mxm->subdev;
	struct nvkm_bios *bios = subdev->device->bios;
	u8  ver, hdr, cnt, len;
	u16 dcb = dcb_table(bios, &ver, &hdr, &cnt, &len);
	if (dcb == 0x0000 || (ver != 0x40 && ver != 0x41)) {
		nvkm_warn(subdev, "unsupported DCB version\n");
		return;
	}

	dcb_outp_foreach(bios, mxm, mxm_dcb_sanitise_entry);
	mxms_foreach(mxm, 0x01, mxm_show_unmatched, NULL);
}