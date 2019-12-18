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
typedef  unsigned int u16 ;
struct wm8350 {int /*<<< orphan*/  dev; int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int regmap_read (int /*<<< orphan*/ ,int,unsigned int*) ; 

u16 wm8350_reg_read(struct wm8350 *wm8350, int reg)
{
	unsigned int data;
	int err;

	err = regmap_read(wm8350->regmap, reg, &data);
	if (err)
		dev_err(wm8350->dev, "read from reg R%d failed\n", reg);

	return data;
}