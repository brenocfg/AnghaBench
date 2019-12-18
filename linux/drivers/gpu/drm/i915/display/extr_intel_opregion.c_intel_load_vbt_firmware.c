#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct intel_opregion {int /*<<< orphan*/  vbt_size; scalar_t__ vbt_firmware; scalar_t__ vbt; } ;
struct firmware {int /*<<< orphan*/  size; int /*<<< orphan*/  data; } ;
struct TYPE_5__ {TYPE_1__* pdev; } ;
struct drm_i915_private {TYPE_2__ drm; struct intel_opregion opregion; } ;
struct TYPE_6__ {char* vbt_firmware; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG_KMS (char*,char const*) ; 
 int /*<<< orphan*/  DRM_ERROR (char*,char const*,int) ; 
 int EINVAL ; 
 int ENOENT ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 TYPE_3__ i915_modparams ; 
 scalar_t__ intel_bios_is_valid_vbt (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ kmemdup (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  release_firmware (struct firmware const*) ; 
 int request_firmware (struct firmware const**,char const*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int intel_load_vbt_firmware(struct drm_i915_private *dev_priv)
{
	struct intel_opregion *opregion = &dev_priv->opregion;
	const struct firmware *fw = NULL;
	const char *name = i915_modparams.vbt_firmware;
	int ret;

	if (!name || !*name)
		return -ENOENT;

	ret = request_firmware(&fw, name, &dev_priv->drm.pdev->dev);
	if (ret) {
		DRM_ERROR("Requesting VBT firmware \"%s\" failed (%d)\n",
			  name, ret);
		return ret;
	}

	if (intel_bios_is_valid_vbt(fw->data, fw->size)) {
		opregion->vbt_firmware = kmemdup(fw->data, fw->size, GFP_KERNEL);
		if (opregion->vbt_firmware) {
			DRM_DEBUG_KMS("Found valid VBT firmware \"%s\"\n", name);
			opregion->vbt = opregion->vbt_firmware;
			opregion->vbt_size = fw->size;
			ret = 0;
		} else {
			ret = -ENOMEM;
		}
	} else {
		DRM_DEBUG_KMS("Invalid VBT firmware \"%s\"\n", name);
		ret = -EINVAL;
	}

	release_firmware(fw);

	return ret;
}