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
struct TYPE_2__ {int max_width; int max_height; int /*<<< orphan*/ * funcs; scalar_t__ min_height; scalar_t__ min_width; } ;
struct drm_device {TYPE_1__ mode_config; } ;

/* Variables and functions */
 int /*<<< orphan*/  kirin_drm_mode_config_funcs ; 

__attribute__((used)) static void kirin_drm_mode_config_init(struct drm_device *dev)
{
	dev->mode_config.min_width = 0;
	dev->mode_config.min_height = 0;

	dev->mode_config.max_width = 2048;
	dev->mode_config.max_height = 2048;

	dev->mode_config.funcs = &kirin_drm_mode_config_funcs;
}