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
struct TYPE_2__ {int normalize_zpos; int /*<<< orphan*/ * funcs; int /*<<< orphan*/  max_height; int /*<<< orphan*/  max_width; scalar_t__ min_height; scalar_t__ min_width; } ;
struct drm_device {TYPE_1__ mode_config; } ;

/* Variables and functions */
 int /*<<< orphan*/  STI_MAX_FB_HEIGHT ; 
 int /*<<< orphan*/  STI_MAX_FB_WIDTH ; 
 int /*<<< orphan*/  sti_mode_config_funcs ; 

__attribute__((used)) static void sti_mode_config_init(struct drm_device *dev)
{
	dev->mode_config.min_width = 0;
	dev->mode_config.min_height = 0;

	/*
	 * set max width and height as default value.
	 * this value would be used to check framebuffer size limitation
	 * at drm_mode_addfb().
	 */
	dev->mode_config.max_width = STI_MAX_FB_WIDTH;
	dev->mode_config.max_height = STI_MAX_FB_HEIGHT;

	dev->mode_config.funcs = &sti_mode_config_funcs;

	dev->mode_config.normalize_zpos = true;
}