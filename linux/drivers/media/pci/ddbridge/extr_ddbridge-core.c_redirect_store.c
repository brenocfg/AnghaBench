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
 int EINVAL ; 
 int ddb_redirect (unsigned int,unsigned int) ; 
 int /*<<< orphan*/  dev_info (struct device*,char*,unsigned int,unsigned int) ; 
 int sscanf (char const*,char*,unsigned int*,unsigned int*) ; 

__attribute__((used)) static ssize_t redirect_store(struct device *device,
			      struct device_attribute *attr,
			      const char *buf, size_t count)
{
	unsigned int i, p;
	int res;

	if (sscanf(buf, "%x %x\n", &i, &p) != 2)
		return -EINVAL;
	res = ddb_redirect(i, p);
	if (res < 0)
		return res;
	dev_info(device, "redirect: %02x, %02x\n", i, p);
	return count;
}