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
struct ls037v7dw01_panel {int /*<<< orphan*/  resb_gpio; int /*<<< orphan*/  ini_gpio; } ;
struct drm_panel {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  gpiod_set_value_cansleep (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msleep (int) ; 
 struct ls037v7dw01_panel* to_ls037v7dw01_device (struct drm_panel*) ; 

__attribute__((used)) static int ls037v7dw01_disable(struct drm_panel *panel)
{
	struct ls037v7dw01_panel *lcd = to_ls037v7dw01_device(panel);

	gpiod_set_value_cansleep(lcd->ini_gpio, 0);
	gpiod_set_value_cansleep(lcd->resb_gpio, 0);

	/* Wait at least 5 vsyncs after disabling the LCD. */
	msleep(100);

	return 0;
}