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
struct reset_control {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct reset_control*) ; 
 int PTR_ERR (struct reset_control*) ; 
 struct reset_control* __reset_control_get (struct device*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  reset_control_put (struct reset_control*) ; 
 int reset_control_reset (struct reset_control*) ; 

int __device_reset(struct device *dev, bool optional)
{
	struct reset_control *rstc;
	int ret;

	rstc = __reset_control_get(dev, NULL, 0, 0, optional, true);
	if (IS_ERR(rstc))
		return PTR_ERR(rstc);

	ret = reset_control_reset(rstc);

	reset_control_put(rstc);

	return ret;
}