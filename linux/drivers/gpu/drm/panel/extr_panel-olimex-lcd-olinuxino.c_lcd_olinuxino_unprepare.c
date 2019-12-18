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
struct lcd_olinuxino {int prepared; int /*<<< orphan*/  supply; int /*<<< orphan*/  enable_gpio; } ;
struct drm_panel {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  gpiod_set_value_cansleep (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regulator_disable (int /*<<< orphan*/ ) ; 
 struct lcd_olinuxino* to_lcd_olinuxino (struct drm_panel*) ; 

__attribute__((used)) static int lcd_olinuxino_unprepare(struct drm_panel *panel)
{
	struct lcd_olinuxino *lcd = to_lcd_olinuxino(panel);

	if (!lcd->prepared)
		return 0;

	gpiod_set_value_cansleep(lcd->enable_gpio, 0);
	regulator_disable(lcd->supply);

	lcd->prepared = false;

	return 0;
}