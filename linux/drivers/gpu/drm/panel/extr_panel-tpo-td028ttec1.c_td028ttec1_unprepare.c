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
struct td028ttec1_panel {int dummy; } ;
struct drm_panel {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  JBT_REG_OUTPUT_CONTROL ; 
 int /*<<< orphan*/  JBT_REG_POWER_ON_OFF ; 
 int /*<<< orphan*/  JBT_REG_SLEEP_IN ; 
 int /*<<< orphan*/  jbt_reg_write_1 (struct td028ttec1_panel*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  jbt_reg_write_2 (struct td028ttec1_panel*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  jbt_ret_write_0 (struct td028ttec1_panel*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct td028ttec1_panel* to_td028ttec1_device (struct drm_panel*) ; 

__attribute__((used)) static int td028ttec1_unprepare(struct drm_panel *panel)
{
	struct td028ttec1_panel *lcd = to_td028ttec1_device(panel);

	jbt_reg_write_2(lcd, JBT_REG_OUTPUT_CONTROL, 0x8002, NULL);
	jbt_ret_write_0(lcd, JBT_REG_SLEEP_IN, NULL);
	jbt_reg_write_1(lcd, JBT_REG_POWER_ON_OFF, 0x00, NULL);

	return 0;
}