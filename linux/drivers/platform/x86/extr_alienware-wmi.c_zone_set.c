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
struct platform_zone {int dummy; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int alienware_update_led (struct platform_zone*) ; 
 struct platform_zone* match_zone (struct device_attribute*) ; 
 int parse_rgb (char const*,struct platform_zone*) ; 
 int /*<<< orphan*/  pr_err (char*) ; 

__attribute__((used)) static ssize_t zone_set(struct device *dev, struct device_attribute *attr,
			const char *buf, size_t count)
{
	struct platform_zone *target_zone;
	int ret;
	target_zone = match_zone(attr);
	if (target_zone == NULL) {
		pr_err("alienware-wmi: invalid target zone\n");
		return 1;
	}
	ret = parse_rgb(buf, target_zone);
	if (ret)
		return ret;
	ret = alienware_update_led(target_zone);
	return ret ? ret : count;
}