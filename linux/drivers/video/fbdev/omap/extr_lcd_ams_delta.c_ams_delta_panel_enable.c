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
struct lcd_panel {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  gpiod_ndisp ; 
 int /*<<< orphan*/  gpiod_set_value (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  gpiod_vblen ; 

__attribute__((used)) static int ams_delta_panel_enable(struct lcd_panel *panel)
{
	gpiod_set_value(gpiod_ndisp, 1);
	gpiod_set_value(gpiod_vblen, 1);
	return 0;
}