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
typedef  int ssize_t ;

/* Variables and functions */
 int HV_PERF_DOMAIN_MAX ; 
 char* domain_name (int) ; 
 int sprintf (char*,char*,int,char const*) ; 

__attribute__((used)) static ssize_t domains_show(struct device *dev, struct device_attribute *attr,
			    char *page)
{
	int d, n, count = 0;
	const char *str;

	for (d = 0; d < HV_PERF_DOMAIN_MAX; d++) {
		str = domain_name(d);
		if (!str)
			continue;

		n = sprintf(page, "%d: %s\n", d, str);
		if (n < 0)
			break;

		count += n;
		page += n;
	}
	return count;
}