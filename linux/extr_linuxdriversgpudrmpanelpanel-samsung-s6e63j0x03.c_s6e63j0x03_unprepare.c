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
struct s6e63j0x03 {TYPE_2__* bl_dev; } ;
struct drm_panel {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  power; } ;
struct TYPE_4__ {TYPE_1__ props; } ;

/* Variables and functions */
 int /*<<< orphan*/  FB_BLANK_POWERDOWN ; 
 struct s6e63j0x03* panel_to_s6e63j0x03 (struct drm_panel*) ; 
 int s6e63j0x03_power_off (struct s6e63j0x03*) ; 

__attribute__((used)) static int s6e63j0x03_unprepare(struct drm_panel *panel)
{
	struct s6e63j0x03 *ctx = panel_to_s6e63j0x03(panel);
	int ret;

	ret = s6e63j0x03_power_off(ctx);
	if (ret < 0)
		return ret;

	ctx->bl_dev->props.power = FB_BLANK_POWERDOWN;

	return 0;
}