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
typedef  int u16 ;
struct nvkm_mxm {int /*<<< orphan*/  subdev; } ;

/* Variables and functions */
 int* mxms_data (struct nvkm_mxm*) ; 
 int /*<<< orphan*/  nvkm_debug (int /*<<< orphan*/ *,char*,int,int) ; 

u16
mxms_version(struct nvkm_mxm *mxm)
{
	u8 *mxms = mxms_data(mxm);
	u16 version = (mxms[4] << 8) | mxms[5];
	switch (version ) {
	case 0x0200:
	case 0x0201:
	case 0x0300:
		return version;
	default:
		break;
	}

	nvkm_debug(&mxm->subdev, "unknown version %d.%d\n", mxms[4], mxms[5]);
	return 0x0000;
}