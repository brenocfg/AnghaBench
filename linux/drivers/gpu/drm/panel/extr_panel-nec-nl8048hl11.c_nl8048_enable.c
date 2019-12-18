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
struct nl8048_panel {int /*<<< orphan*/  reset_gpio; } ;
struct drm_panel {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  gpiod_set_value_cansleep (int /*<<< orphan*/ ,int) ; 
 struct nl8048_panel* to_nl8048_device (struct drm_panel*) ; 

__attribute__((used)) static int nl8048_enable(struct drm_panel *panel)
{
	struct nl8048_panel *lcd = to_nl8048_device(panel);

	gpiod_set_value_cansleep(lcd->reset_gpio, 1);

	return 0;
}