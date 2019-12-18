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
struct bochs_device {TYPE_2__* dev; int /*<<< orphan*/  connector; int /*<<< orphan*/  pipe; int /*<<< orphan*/  fb_base; } ;
struct TYPE_6__ {int max_width; int max_height; int preferred_depth; int prefer_shadow_fbdev; int quirk_addfb_prefer_host_byte_order; int /*<<< orphan*/ * funcs; scalar_t__ prefer_shadow; int /*<<< orphan*/  fb_base; } ;
struct TYPE_7__ {TYPE_1__ mode_config; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bochs_connector_init (TYPE_2__*) ; 
 int /*<<< orphan*/  bochs_formats ; 
 int /*<<< orphan*/  bochs_mode_funcs ; 
 int /*<<< orphan*/  bochs_pipe_funcs ; 
 int /*<<< orphan*/  drm_mode_config_init (TYPE_2__*) ; 
 int /*<<< orphan*/  drm_mode_config_reset (TYPE_2__*) ; 
 int /*<<< orphan*/  drm_simple_display_pipe_init (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int bochs_kms_init(struct bochs_device *bochs)
{
	drm_mode_config_init(bochs->dev);

	bochs->dev->mode_config.max_width = 8192;
	bochs->dev->mode_config.max_height = 8192;

	bochs->dev->mode_config.fb_base = bochs->fb_base;
	bochs->dev->mode_config.preferred_depth = 24;
	bochs->dev->mode_config.prefer_shadow = 0;
	bochs->dev->mode_config.prefer_shadow_fbdev = 1;
	bochs->dev->mode_config.quirk_addfb_prefer_host_byte_order = true;

	bochs->dev->mode_config.funcs = &bochs_mode_funcs;

	bochs_connector_init(bochs->dev);
	drm_simple_display_pipe_init(bochs->dev,
				     &bochs->pipe,
				     &bochs_pipe_funcs,
				     bochs_formats,
				     ARRAY_SIZE(bochs_formats),
				     NULL,
				     &bochs->connector);

	drm_mode_config_reset(bochs->dev);

	return 0;
}