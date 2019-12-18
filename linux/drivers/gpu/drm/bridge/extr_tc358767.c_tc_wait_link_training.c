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
typedef  int u32 ;
struct tc_data {int /*<<< orphan*/  regmap; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DP0_LTSTAT ; 
 int /*<<< orphan*/  LT_LOOPDONE ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int tc_poll_timeout (struct tc_data*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static int tc_wait_link_training(struct tc_data *tc)
{
	u32 value;
	int ret;

	ret = tc_poll_timeout(tc, DP0_LTSTAT, LT_LOOPDONE,
			      LT_LOOPDONE, 1, 1000);
	if (ret) {
		dev_err(tc->dev, "Link training timeout waiting for LT_LOOPDONE!\n");
		return ret;
	}

	ret = regmap_read(tc->regmap, DP0_LTSTAT, &value);
	if (ret)
		return ret;

	return (value >> 8) & 0x7;
}