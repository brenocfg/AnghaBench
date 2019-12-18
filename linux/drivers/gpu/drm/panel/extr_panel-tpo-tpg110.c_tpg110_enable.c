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
typedef  int /*<<< orphan*/  u8 ;
struct tpg110 {int /*<<< orphan*/  backlight; } ;
struct drm_panel {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  TPG110_CTRL2_PM ; 
 int /*<<< orphan*/  backlight_enable (int /*<<< orphan*/ ) ; 
 struct tpg110* to_tpg110 (struct drm_panel*) ; 
 int /*<<< orphan*/  tpg110_read_reg (struct tpg110*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tpg110_write_reg (struct tpg110*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int tpg110_enable(struct drm_panel *panel)
{
	struct tpg110 *tpg = to_tpg110(panel);
	u8 val;

	backlight_enable(tpg->backlight);

	/* Take chip out of standby */
	val = tpg110_read_reg(tpg, TPG110_CTRL2_PM);
	val |= TPG110_CTRL2_PM;
	tpg110_write_reg(tpg, TPG110_CTRL2_PM, val);

	return 0;
}