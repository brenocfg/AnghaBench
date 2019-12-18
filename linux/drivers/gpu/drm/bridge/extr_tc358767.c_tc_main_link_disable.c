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
struct tc_data {int /*<<< orphan*/  regmap; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DP0CTL ; 
 int /*<<< orphan*/  DP0_SRCCTRL ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*) ; 
 int regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int tc_main_link_disable(struct tc_data *tc)
{
	int ret;

	dev_dbg(tc->dev, "link disable\n");

	ret = regmap_write(tc->regmap, DP0_SRCCTRL, 0);
	if (ret)
		return ret;

	return regmap_write(tc->regmap, DP0CTL, 0);
}