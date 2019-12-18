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
struct lcd_olinuxino {int /*<<< orphan*/  panel; } ;
struct i2c_client {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  drm_panel_remove (int /*<<< orphan*/ *) ; 
 struct lcd_olinuxino* i2c_get_clientdata (struct i2c_client*) ; 
 int /*<<< orphan*/  lcd_olinuxino_disable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lcd_olinuxino_unprepare (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int lcd_olinuxino_remove(struct i2c_client *client)
{
	struct lcd_olinuxino *panel = i2c_get_clientdata(client);

	drm_panel_remove(&panel->panel);

	lcd_olinuxino_disable(&panel->panel);
	lcd_olinuxino_unprepare(&panel->panel);

	return 0;
}