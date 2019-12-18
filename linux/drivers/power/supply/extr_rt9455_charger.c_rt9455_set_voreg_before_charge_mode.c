#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct rt9455_info {int /*<<< orphan*/  voreg; TYPE_1__* client; } ;
struct device {int dummy; } ;
struct TYPE_2__ {struct device dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  F_VOREG ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 int rt9455_set_field_val (struct rt9455_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rt9455_voreg_values ; 

__attribute__((used)) static int rt9455_set_voreg_before_charge_mode(struct rt9455_info *info)
{
	struct device *dev = &info->client->dev;
	int ret;

	ret = rt9455_set_field_val(info, F_VOREG,
				   rt9455_voreg_values,
				   ARRAY_SIZE(rt9455_voreg_values),
				   info->voreg);
	if (ret) {
		dev_err(dev, "Failed to set VOREG value\n");
		return ret;
	}

	return 0;
}