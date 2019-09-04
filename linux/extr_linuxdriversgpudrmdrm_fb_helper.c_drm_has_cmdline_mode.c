#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct drm_fb_helper_connector {TYPE_2__* connector; } ;
struct TYPE_3__ {int specified; } ;
struct TYPE_4__ {TYPE_1__ cmdline_mode; } ;

/* Variables and functions */

__attribute__((used)) static bool drm_has_cmdline_mode(struct drm_fb_helper_connector *fb_connector)
{
	return fb_connector->connector->cmdline_mode.specified;
}