#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct bochs_device {int mode_config_initialized; int /*<<< orphan*/  encoder; int /*<<< orphan*/  connector; TYPE_2__* dev; int /*<<< orphan*/  fb_base; } ;
struct TYPE_6__ {int max_width; int max_height; int preferred_depth; int /*<<< orphan*/ * funcs; scalar_t__ prefer_shadow; int /*<<< orphan*/  fb_base; } ;
struct TYPE_7__ {TYPE_1__ mode_config; } ;

/* Variables and functions */
 int /*<<< orphan*/  bochs_connector_init (TYPE_2__*) ; 
 int /*<<< orphan*/  bochs_crtc_init (TYPE_2__*) ; 
 int /*<<< orphan*/  bochs_encoder_init (TYPE_2__*) ; 
 int /*<<< orphan*/  bochs_mode_funcs ; 
 int /*<<< orphan*/  drm_connector_attach_encoder (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  drm_mode_config_init (TYPE_2__*) ; 

int bochs_kms_init(struct bochs_device *bochs)
{
	drm_mode_config_init(bochs->dev);
	bochs->mode_config_initialized = true;

	bochs->dev->mode_config.max_width = 8192;
	bochs->dev->mode_config.max_height = 8192;

	bochs->dev->mode_config.fb_base = bochs->fb_base;
	bochs->dev->mode_config.preferred_depth = 24;
	bochs->dev->mode_config.prefer_shadow = 0;

	bochs->dev->mode_config.funcs = &bochs_mode_funcs;

	bochs_crtc_init(bochs->dev);
	bochs_encoder_init(bochs->dev);
	bochs_connector_init(bochs->dev);
	drm_connector_attach_encoder(&bochs->connector,
					  &bochs->encoder);

	return 0;
}