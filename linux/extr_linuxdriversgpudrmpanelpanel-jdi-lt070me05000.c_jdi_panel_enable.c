#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct jdi_panel {int enabled; int /*<<< orphan*/  backlight; } ;
struct drm_panel {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  backlight_enable (int /*<<< orphan*/ ) ; 
 struct jdi_panel* to_jdi_panel (struct drm_panel*) ; 

__attribute__((used)) static int jdi_panel_enable(struct drm_panel *panel)
{
	struct jdi_panel *jdi = to_jdi_panel(panel);

	if (jdi->enabled)
		return 0;

	backlight_enable(jdi->backlight);

	jdi->enabled = true;

	return 0;
}