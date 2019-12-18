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
struct file {int dummy; } ;
struct bin_attribute {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;
typedef  scalar_t__ loff_t ;

/* Variables and functions */
 int /*<<< orphan*/  EFAULT ; 
 int /*<<< orphan*/  W1_F29_REG_COND_SEARCH_POL_SELECT ; 
 int /*<<< orphan*/  _read_reg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  kobj_to_w1_slave (struct kobject*) ; 

__attribute__((used)) static ssize_t cond_search_polarity_read(struct file *filp,
					 struct kobject *kobj,
					 struct bin_attribute *bin_attr,
					 char *buf, loff_t off, size_t count)
{
	if (count != 1 || off != 0)
		return -EFAULT;
	return _read_reg(kobj_to_w1_slave(kobj),
		W1_F29_REG_COND_SEARCH_POL_SELECT, buf);
}