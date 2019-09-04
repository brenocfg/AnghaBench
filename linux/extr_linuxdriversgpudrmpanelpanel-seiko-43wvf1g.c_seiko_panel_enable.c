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
struct seiko_panel {int enabled; TYPE_2__* backlight; } ;
struct drm_panel {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  power; int /*<<< orphan*/  state; } ;
struct TYPE_4__ {TYPE_1__ props; } ;

/* Variables and functions */
 int /*<<< orphan*/  BL_CORE_FBBLANK ; 
 int /*<<< orphan*/  FB_BLANK_UNBLANK ; 
 int /*<<< orphan*/  backlight_update_status (TYPE_2__*) ; 
 struct seiko_panel* to_seiko_panel (struct drm_panel*) ; 

__attribute__((used)) static int seiko_panel_enable(struct drm_panel *panel)
{
	struct seiko_panel *p = to_seiko_panel(panel);

	if (p->enabled)
		return 0;

	if (p->backlight) {
		p->backlight->props.state &= ~BL_CORE_FBBLANK;
		p->backlight->props.power = FB_BLANK_UNBLANK;
		backlight_update_status(p->backlight);
	}

	p->enabled = true;

	return 0;
}