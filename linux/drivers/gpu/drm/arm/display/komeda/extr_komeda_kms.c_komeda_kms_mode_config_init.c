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
struct drm_mode_config {int max_width; int max_height; int allow_fb_modifiers; int /*<<< orphan*/ * helper_private; int /*<<< orphan*/ * funcs; scalar_t__ min_height; scalar_t__ min_width; } ;
struct TYPE_2__ {struct drm_mode_config mode_config; } ;
struct komeda_kms_dev {TYPE_1__ base; } ;
struct komeda_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  drm_mode_config_init (TYPE_1__*) ; 
 int /*<<< orphan*/  komeda_kms_setup_crtcs (struct komeda_kms_dev*,struct komeda_dev*) ; 
 int /*<<< orphan*/  komeda_mode_config_funcs ; 
 int /*<<< orphan*/  komeda_mode_config_helpers ; 

__attribute__((used)) static void komeda_kms_mode_config_init(struct komeda_kms_dev *kms,
					struct komeda_dev *mdev)
{
	struct drm_mode_config *config = &kms->base.mode_config;

	drm_mode_config_init(&kms->base);

	komeda_kms_setup_crtcs(kms, mdev);

	/* Get value from dev */
	config->min_width	= 0;
	config->min_height	= 0;
	config->max_width	= 4096;
	config->max_height	= 4096;
	config->allow_fb_modifiers = true;

	config->funcs = &komeda_mode_config_funcs;
	config->helper_private = &komeda_mode_config_helpers;
}