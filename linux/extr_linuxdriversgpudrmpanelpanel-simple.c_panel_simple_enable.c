#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct panel_simple {int enabled; TYPE_4__* backlight; TYPE_3__* desc; } ;
struct drm_panel {int dummy; } ;
struct TYPE_5__ {int /*<<< orphan*/  power; int /*<<< orphan*/  state; } ;
struct TYPE_8__ {TYPE_1__ props; } ;
struct TYPE_6__ {scalar_t__ enable; } ;
struct TYPE_7__ {TYPE_2__ delay; } ;

/* Variables and functions */
 int /*<<< orphan*/  BL_CORE_FBBLANK ; 
 int /*<<< orphan*/  FB_BLANK_UNBLANK ; 
 int /*<<< orphan*/  backlight_update_status (TYPE_4__*) ; 
 int /*<<< orphan*/  msleep (scalar_t__) ; 
 struct panel_simple* to_panel_simple (struct drm_panel*) ; 

__attribute__((used)) static int panel_simple_enable(struct drm_panel *panel)
{
	struct panel_simple *p = to_panel_simple(panel);

	if (p->enabled)
		return 0;

	if (p->desc->delay.enable)
		msleep(p->desc->delay.enable);

	if (p->backlight) {
		p->backlight->props.state &= ~BL_CORE_FBBLANK;
		p->backlight->props.power = FB_BLANK_UNBLANK;
		backlight_update_status(p->backlight);
	}

	p->enabled = true;

	return 0;
}