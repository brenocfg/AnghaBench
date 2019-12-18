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
 int /*<<< orphan*/  MSR_IA32_TEMPERATURE_TARGET ; 
 int rdmsrl_safe (int /*<<< orphan*/ ,int*) ; 
 int sprintf (char*,char*,int) ; 

__attribute__((used)) static ssize_t tcc_offset_degree_celsius_show(struct device *dev,
			       struct device_attribute *attr, char *buf)
{
	u64 val;
	int err;

	err = rdmsrl_safe(MSR_IA32_TEMPERATURE_TARGET, &val);
	if (err)
		return err;

	val = (val >> 24) & 0xff;
	return sprintf(buf, "%d\n", (int)val);
}