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
struct nvkm_subdev {int dummy; } ;
struct nvkm_secboot {int wpr_set; int /*<<< orphan*/  halt_falcon; TYPE_1__* func; struct nvkm_subdev subdev; } ;
struct acr_r352 {int /*<<< orphan*/ * falcon_state; scalar_t__ unload_blob; } ;
struct TYPE_2__ {int (* run_blob ) (struct nvkm_secboot*,scalar_t__,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  NON_SECURE ; 
 int NVKM_SECBOOT_FALCON_END ; 
 int /*<<< orphan*/  nvkm_debug (struct nvkm_subdev*,char*) ; 
 int /*<<< orphan*/  nvkm_error (struct nvkm_subdev*,char*,int) ; 
 int stub1 (struct nvkm_secboot*,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
acr_r352_shutdown(struct acr_r352 *acr, struct nvkm_secboot *sb)
{
	struct nvkm_subdev *subdev = &sb->subdev;
	int i;

	/* Run the unload blob to unprotect the WPR region */
	if (acr->unload_blob && sb->wpr_set) {
		int ret;

		nvkm_debug(subdev, "running HS unload blob\n");
		ret = sb->func->run_blob(sb, acr->unload_blob, sb->halt_falcon);
		if (ret < 0)
			return ret;
		/*
		 * Unload blob will return this error code - it is not an error
		 * and the expected behavior on RM as well
		 */
		if (ret && ret != 0x1d) {
			nvkm_error(subdev, "HS unload failed, ret 0x%08x\n", ret);
			return -EINVAL;
		}
		nvkm_debug(subdev, "HS unload blob completed\n");
	}

	for (i = 0; i < NVKM_SECBOOT_FALCON_END; i++)
		acr->falcon_state[i] = NON_SECURE;

	sb->wpr_set = false;

	return 0;
}