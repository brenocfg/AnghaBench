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
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  LM3533_REG_PATTERN_FALLTIME_BASE ; 
 int /*<<< orphan*/  store_risefalltime (struct device*,struct device_attribute*,char const*,size_t,int /*<<< orphan*/ ) ; 

__attribute__((used)) static ssize_t store_falltime(struct device *dev,
					struct device_attribute *attr,
					const char *buf, size_t len)
{
	return store_risefalltime(dev, attr, buf, len,
					LM3533_REG_PATTERN_FALLTIME_BASE);
}