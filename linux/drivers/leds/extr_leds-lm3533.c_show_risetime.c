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
 int /*<<< orphan*/  LM3533_REG_PATTERN_RISETIME_BASE ; 
 int /*<<< orphan*/  show_risefalltime (struct device*,struct device_attribute*,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static ssize_t show_risetime(struct device *dev,
				struct device_attribute *attr, char *buf)
{
	return show_risefalltime(dev, attr, buf,
					LM3533_REG_PATTERN_RISETIME_BASE);
}