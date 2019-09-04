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
struct ili9322 {int dummy; } ;
struct drm_panel {int dummy; } ;

/* Variables and functions */
 int ili9322_init (struct drm_panel*,struct ili9322*) ; 
 int ili9322_power_on (struct ili9322*) ; 
 int /*<<< orphan*/  ili9322_unprepare (struct drm_panel*) ; 
 struct ili9322* panel_to_ili9322 (struct drm_panel*) ; 

__attribute__((used)) static int ili9322_prepare(struct drm_panel *panel)
{
	struct ili9322 *ili = panel_to_ili9322(panel);
	int ret;

	ret = ili9322_power_on(ili);
	if (ret < 0)
		return ret;

	ret = ili9322_init(panel, ili);
	if (ret < 0)
		ili9322_unprepare(panel);

	return ret;
}