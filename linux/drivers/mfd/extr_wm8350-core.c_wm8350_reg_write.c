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
typedef  int /*<<< orphan*/  u16 ;
struct wm8350 {int /*<<< orphan*/  dev; int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int regmap_write (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

int wm8350_reg_write(struct wm8350 *wm8350, int reg, u16 val)
{
	int ret;

	ret = regmap_write(wm8350->regmap, reg, val);

	if (ret)
		dev_err(wm8350->dev, "write to reg R%d failed\n", reg);
	return ret;
}