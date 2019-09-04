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
struct device {unsigned int id; } ;
typedef  size_t ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/ * capabilities ; 
 int /*<<< orphan*/ * err_data_buffer ; 
 int /*<<< orphan*/ * err_struct_info ; 
 int /*<<< orphan*/ * err_type_info ; 
 int /*<<< orphan*/  ia64_pal_mc_error_inject_phys (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ia64_pal_mc_error_inject_virt (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ia64_tpa (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * resources ; 
 unsigned long simple_strtoull (char const*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * status ; 

__attribute__((used)) static ssize_t
store_call_start(struct device *dev, struct device_attribute *attr,
		const char *buf, size_t size)
{
	unsigned int cpu=dev->id;
	unsigned long call_start = simple_strtoull(buf, NULL, 16);

#ifdef ERR_INJ_DEBUG
	printk(KERN_DEBUG "pal_mc_err_inject for cpu%d:\n", cpu);
	printk(KERN_DEBUG "err_type_info=%lx,\n", err_type_info[cpu]);
	printk(KERN_DEBUG "err_struct_info=%lx,\n", err_struct_info[cpu]);
	printk(KERN_DEBUG "err_data_buffer=%lx, %lx, %lx.\n",
			  err_data_buffer[cpu].data1,
			  err_data_buffer[cpu].data2,
			  err_data_buffer[cpu].data3);
#endif
	switch (call_start) {
	    case 0: /* Do nothing. */
		break;
	    case 1: /* Call pal_mc_error_inject in physical mode. */
		status[cpu]=ia64_pal_mc_error_inject_phys(err_type_info[cpu],
					err_struct_info[cpu],
					ia64_tpa(&err_data_buffer[cpu]),
					&capabilities[cpu],
			 		&resources[cpu]);
		break;
	    case 2: /* Call pal_mc_error_inject in virtual mode. */
		status[cpu]=ia64_pal_mc_error_inject_virt(err_type_info[cpu],
					err_struct_info[cpu],
					ia64_tpa(&err_data_buffer[cpu]),
					&capabilities[cpu],
			 		&resources[cpu]);
		break;
	    default:
		status[cpu] = -EINVAL;
		break;
	}

#ifdef ERR_INJ_DEBUG
	printk(KERN_DEBUG "Returns: status=%d,\n", (int)status[cpu]);
	printk(KERN_DEBUG "capabilities=%lx,\n", capabilities[cpu]);
	printk(KERN_DEBUG "resources=%lx\n", resources[cpu]);
#endif
	return size;
}