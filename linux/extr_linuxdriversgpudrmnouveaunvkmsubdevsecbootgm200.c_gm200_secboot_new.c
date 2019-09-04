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
struct nvkm_secboot {int dummy; } ;
struct nvkm_device {int dummy; } ;
struct nvkm_acr {int dummy; } ;
struct gm200_secboot {struct nvkm_secboot base; } ;

/* Variables and functions */
 int BIT (int /*<<< orphan*/ ) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (struct nvkm_acr*) ; 
 int /*<<< orphan*/  NVKM_SECBOOT_FALCON_FECS ; 
 int /*<<< orphan*/  NVKM_SECBOOT_FALCON_GPCCS ; 
 int PTR_ERR (struct nvkm_acr*) ; 
 struct nvkm_acr* acr_r361_new (int) ; 
 int /*<<< orphan*/  gm200_secboot ; 
 struct gm200_secboot* kzalloc (int,int /*<<< orphan*/ ) ; 
 int nvkm_secboot_ctor (int /*<<< orphan*/ *,struct nvkm_acr*,struct nvkm_device*,int,struct nvkm_secboot*) ; 

int
gm200_secboot_new(struct nvkm_device *device, int index,
		  struct nvkm_secboot **psb)
{
	int ret;
	struct gm200_secboot *gsb;
	struct nvkm_acr *acr;

	acr = acr_r361_new(BIT(NVKM_SECBOOT_FALCON_FECS) |
			   BIT(NVKM_SECBOOT_FALCON_GPCCS));
	if (IS_ERR(acr))
		return PTR_ERR(acr);

	gsb = kzalloc(sizeof(*gsb), GFP_KERNEL);
	if (!gsb) {
		psb = NULL;
		return -ENOMEM;
	}
	*psb = &gsb->base;

	ret = nvkm_secboot_ctor(&gm200_secboot, acr, device, index, &gsb->base);
	if (ret)
		return ret;

	return 0;
}