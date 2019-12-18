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
struct firmware {int dummy; } ;
struct drm_device {int /*<<< orphan*/  dev; } ;
struct TYPE_2__ {struct drm_device* dev; } ;
struct adreno_gpu {scalar_t__ fwloc; TYPE_1__ base; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEV_ERROR (int /*<<< orphan*/ ,char*,char const*,...) ; 
 int /*<<< orphan*/  DRM_DEV_INFO (int /*<<< orphan*/ ,char*,char*) ; 
 int ENOENT ; 
 int ENOMEM ; 
 struct firmware const* ERR_PTR (int) ; 
 scalar_t__ FW_LOCATION_HELPER ; 
 scalar_t__ FW_LOCATION_LEGACY ; 
 scalar_t__ FW_LOCATION_NEW ; 
 scalar_t__ FW_LOCATION_UNKNOWN ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 char* kasprintf (int /*<<< orphan*/ ,char*,char const*) ; 
 int /*<<< orphan*/  kfree (char*) ; 
 int request_firmware (struct firmware const**,char*,int /*<<< orphan*/ ) ; 
 int request_firmware_direct (struct firmware const**,char const*,int /*<<< orphan*/ ) ; 

const struct firmware *
adreno_request_fw(struct adreno_gpu *adreno_gpu, const char *fwname)
{
	struct drm_device *drm = adreno_gpu->base.dev;
	const struct firmware *fw = NULL;
	char *newname;
	int ret;

	newname = kasprintf(GFP_KERNEL, "qcom/%s", fwname);
	if (!newname)
		return ERR_PTR(-ENOMEM);

	/*
	 * Try first to load from qcom/$fwfile using a direct load (to avoid
	 * a potential timeout waiting for usermode helper)
	 */
	if ((adreno_gpu->fwloc == FW_LOCATION_UNKNOWN) ||
	    (adreno_gpu->fwloc == FW_LOCATION_NEW)) {

		ret = request_firmware_direct(&fw, newname, drm->dev);
		if (!ret) {
			DRM_DEV_INFO(drm->dev, "loaded %s from new location\n",
				newname);
			adreno_gpu->fwloc = FW_LOCATION_NEW;
			goto out;
		} else if (adreno_gpu->fwloc != FW_LOCATION_UNKNOWN) {
			DRM_DEV_ERROR(drm->dev, "failed to load %s: %d\n",
				newname, ret);
			fw = ERR_PTR(ret);
			goto out;
		}
	}

	/*
	 * Then try the legacy location without qcom/ prefix
	 */
	if ((adreno_gpu->fwloc == FW_LOCATION_UNKNOWN) ||
	    (adreno_gpu->fwloc == FW_LOCATION_LEGACY)) {

		ret = request_firmware_direct(&fw, fwname, drm->dev);
		if (!ret) {
			DRM_DEV_INFO(drm->dev, "loaded %s from legacy location\n",
				newname);
			adreno_gpu->fwloc = FW_LOCATION_LEGACY;
			goto out;
		} else if (adreno_gpu->fwloc != FW_LOCATION_UNKNOWN) {
			DRM_DEV_ERROR(drm->dev, "failed to load %s: %d\n",
				fwname, ret);
			fw = ERR_PTR(ret);
			goto out;
		}
	}

	/*
	 * Finally fall back to request_firmware() for cases where the
	 * usermode helper is needed (I think mainly android)
	 */
	if ((adreno_gpu->fwloc == FW_LOCATION_UNKNOWN) ||
	    (adreno_gpu->fwloc == FW_LOCATION_HELPER)) {

		ret = request_firmware(&fw, newname, drm->dev);
		if (!ret) {
			DRM_DEV_INFO(drm->dev, "loaded %s with helper\n",
				newname);
			adreno_gpu->fwloc = FW_LOCATION_HELPER;
			goto out;
		} else if (adreno_gpu->fwloc != FW_LOCATION_UNKNOWN) {
			DRM_DEV_ERROR(drm->dev, "failed to load %s: %d\n",
				newname, ret);
			fw = ERR_PTR(ret);
			goto out;
		}
	}

	DRM_DEV_ERROR(drm->dev, "failed to load %s\n", fwname);
	fw = ERR_PTR(-ENOENT);
out:
	kfree(newname);
	return fw;
}