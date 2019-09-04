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
struct kobject {int dummy; } ;
struct kobj_attribute {int dummy; } ;
typedef  size_t ssize_t ;

/* Variables and functions */
 size_t EINVAL ; 
 unsigned long rtas_poweron_auto ; 
 int sscanf (char const*,char*,unsigned long*) ; 

__attribute__((used)) static ssize_t auto_poweron_store(struct kobject *kobj,
				  struct kobj_attribute *attr,
				  const char *buf, size_t n)
{
	int ret;
	unsigned long ups_restart;
	ret = sscanf(buf, "%lu", &ups_restart);

	if ((ret == 1) && ((ups_restart == 1) || (ups_restart == 0))){
		rtas_poweron_auto = ups_restart;
		return n;
	}
	return -EINVAL;
}