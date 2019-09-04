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
struct rpi_touchscreen {int dummy; } ;
struct drm_panel {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  REG_POWERON ; 
 int /*<<< orphan*/  REG_PWM ; 
 struct rpi_touchscreen* panel_to_ts (struct drm_panel*) ; 
 int /*<<< orphan*/  rpi_touchscreen_i2c_write (struct rpi_touchscreen*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int rpi_touchscreen_disable(struct drm_panel *panel)
{
	struct rpi_touchscreen *ts = panel_to_ts(panel);

	rpi_touchscreen_i2c_write(ts, REG_PWM, 0);

	rpi_touchscreen_i2c_write(ts, REG_POWERON, 0);
	udelay(1);

	return 0;
}