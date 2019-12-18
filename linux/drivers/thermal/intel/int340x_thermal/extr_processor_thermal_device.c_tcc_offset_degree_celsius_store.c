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
typedef  int u64 ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int BIT (int) ; 
 int EACCES ; 
 int EINVAL ; 
 int /*<<< orphan*/  MSR_PLATFORM_INFO ; 
 scalar_t__ kstrtoint (char const*,int /*<<< orphan*/ ,int*) ; 
 int rdmsrl_safe (int /*<<< orphan*/ ,int*) ; 
 int tcc_offset_save ; 
 int tcc_offset_update (int) ; 

__attribute__((used)) static ssize_t tcc_offset_degree_celsius_store(struct device *dev,
				struct device_attribute *attr, const char *buf,
				size_t count)
{
	u64 val;
	int tcc, err;

	err = rdmsrl_safe(MSR_PLATFORM_INFO, &val);
	if (err)
		return err;

	if (!(val & BIT(30)))
		return -EACCES;

	if (kstrtoint(buf, 0, &tcc))
		return -EINVAL;

	err = tcc_offset_update(tcc);
	if (err)
		return err;

	tcc_offset_save = tcc;

	return count;
}