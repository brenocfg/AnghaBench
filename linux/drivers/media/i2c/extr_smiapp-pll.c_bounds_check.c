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
typedef  scalar_t__ uint32_t ;
struct device {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*,char*,scalar_t__,scalar_t__,scalar_t__) ; 

__attribute__((used)) static int bounds_check(struct device *dev, uint32_t val,
			uint32_t min, uint32_t max, char *str)
{
	if (val >= min && val <= max)
		return 0;

	dev_dbg(dev, "%s out of bounds: %d (%d--%d)\n", str, val, min, max);

	return -EINVAL;
}