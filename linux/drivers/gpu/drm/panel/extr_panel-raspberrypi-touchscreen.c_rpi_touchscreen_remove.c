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
struct rpi_touchscreen {int /*<<< orphan*/  dsi; int /*<<< orphan*/  base; } ;
struct i2c_client {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  drm_panel_remove (int /*<<< orphan*/ *) ; 
 struct rpi_touchscreen* i2c_get_clientdata (struct i2c_client*) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mipi_dsi_detach (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mipi_dsi_device_unregister (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int rpi_touchscreen_remove(struct i2c_client *i2c)
{
	struct rpi_touchscreen *ts = i2c_get_clientdata(i2c);

	mipi_dsi_detach(ts->dsi);

	drm_panel_remove(&ts->base);

	mipi_dsi_device_unregister(ts->dsi);
	kfree(ts->dsi);

	return 0;
}