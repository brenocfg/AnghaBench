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
struct TYPE_2__ {int max_width; int max_height; int preferred_depth; int /*<<< orphan*/ * funcs; scalar_t__ prefer_shadow; scalar_t__ min_height; scalar_t__ min_width; } ;
struct drm_device {TYPE_1__ mode_config; } ;
struct cirrus_device {struct drm_device dev; } ;

/* Variables and functions */
 int CIRRUS_MAX_PITCH ; 
 int /*<<< orphan*/  cirrus_mode_config_funcs ; 
 int /*<<< orphan*/  drm_mode_config_init (struct drm_device*) ; 

__attribute__((used)) static void cirrus_mode_config_init(struct cirrus_device *cirrus)
{
	struct drm_device *dev = &cirrus->dev;

	drm_mode_config_init(dev);
	dev->mode_config.min_width = 0;
	dev->mode_config.min_height = 0;
	dev->mode_config.max_width = CIRRUS_MAX_PITCH / 2;
	dev->mode_config.max_height = 1024;
	dev->mode_config.preferred_depth = 16;
	dev->mode_config.prefer_shadow = 0;
	dev->mode_config.funcs = &cirrus_mode_config_funcs;
}