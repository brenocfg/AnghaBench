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
struct nvkm_mxm {int /*<<< orphan*/ * mxms; int /*<<< orphan*/  subdev; } ;
struct mxm_shadow_h {scalar_t__ (* exec ) (struct nvkm_mxm*,int /*<<< orphan*/ ) ;scalar_t__ name; } ;

/* Variables and functions */
 int ENOENT ; 
 struct mxm_shadow_h* _mxm_shadow ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 scalar_t__ mxms_valid (struct nvkm_mxm*) ; 
 int /*<<< orphan*/  nvkm_debug (int /*<<< orphan*/ *,char*,scalar_t__) ; 
 scalar_t__ stub1 (struct nvkm_mxm*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
mxm_shadow(struct nvkm_mxm *mxm, u8 version)
{
	struct mxm_shadow_h *shadow = _mxm_shadow;
	do {
		nvkm_debug(&mxm->subdev, "checking %s\n", shadow->name);
		if (shadow->exec(mxm, version)) {
			if (mxms_valid(mxm))
				return 0;
			kfree(mxm->mxms);
			mxm->mxms = NULL;
		}
	} while ((++shadow)->name);
	return -ENOENT;
}