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
struct mdp5_kms {int /*<<< orphan*/  num_hwmixers; struct mdp5_hw_mixer** hwmixers; int /*<<< orphan*/  cfg; struct drm_device* dev; } ;
struct mdp5_hw_mixer {int /*<<< orphan*/  idx; } ;
struct TYPE_2__ {int count; int /*<<< orphan*/ * instances; } ;
struct mdp5_cfg_hw {TYPE_1__ lm; } ;
struct drm_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEV_ERROR (int /*<<< orphan*/ ,char*,int,int) ; 
 scalar_t__ IS_ERR (struct mdp5_hw_mixer*) ; 
 int PTR_ERR (struct mdp5_hw_mixer*) ; 
 struct mdp5_cfg_hw* mdp5_cfg_get_hw_config (int /*<<< orphan*/ ) ; 
 struct mdp5_hw_mixer* mdp5_mixer_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int hwmixer_init(struct mdp5_kms *mdp5_kms)
{
	struct drm_device *dev = mdp5_kms->dev;
	const struct mdp5_cfg_hw *hw_cfg;
	int i, ret;

	hw_cfg = mdp5_cfg_get_hw_config(mdp5_kms->cfg);

	for (i = 0; i < hw_cfg->lm.count; i++) {
		struct mdp5_hw_mixer *mixer;

		mixer = mdp5_mixer_init(&hw_cfg->lm.instances[i]);
		if (IS_ERR(mixer)) {
			ret = PTR_ERR(mixer);
			DRM_DEV_ERROR(dev->dev, "failed to construct LM%d (%d)\n",
				i, ret);
			return ret;
		}

		mixer->idx = mdp5_kms->num_hwmixers;
		mdp5_kms->hwmixers[mdp5_kms->num_hwmixers++] = mixer;
	}

	return 0;
}