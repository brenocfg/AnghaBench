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
 int regmap_bulk_write (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int) ; 

int wm8350_block_write(struct wm8350 *wm8350, int start_reg, int regs,
		       u16 *src)
{
	int ret = 0;

	ret = regmap_bulk_write(wm8350->regmap, start_reg, src, regs);
	if (ret)
		dev_err(wm8350->dev, "block write starting at R%d failed\n",
			start_reg);

	return ret;
}