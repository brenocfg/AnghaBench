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
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  size_t ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  ipoib_set_umcast (int /*<<< orphan*/ ,unsigned long) ; 
 unsigned long simple_strtoul (char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  to_net_dev (struct device*) ; 

__attribute__((used)) static ssize_t set_umcast(struct device *dev,
			  struct device_attribute *attr,
			  const char *buf, size_t count)
{
	unsigned long umcast_val = simple_strtoul(buf, NULL, 0);

	ipoib_set_umcast(to_net_dev(dev), umcast_val);

	return count;
}