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
typedef  int u64 ;
struct nvkm_subdev {int dummy; } ;
struct nvkm_mxm {struct nvkm_subdev subdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  nvkm_info (struct nvkm_subdev*,char*,int) ; 

__attribute__((used)) static bool
mxm_show_unmatched(struct nvkm_mxm *mxm, u8 *data, void *info)
{
	struct nvkm_subdev *subdev = &mxm->subdev;
	u64 desc = *(u64 *)data;
	if ((desc & 0xf0) != 0xf0)
		nvkm_info(subdev, "unmatched output device %016llx\n", desc);
	return true;
}