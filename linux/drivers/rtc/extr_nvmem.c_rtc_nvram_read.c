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
struct bin_attribute {int /*<<< orphan*/  private; } ;
typedef  int /*<<< orphan*/  ssize_t ;
typedef  int /*<<< orphan*/  loff_t ;

/* Variables and functions */
 int /*<<< orphan*/  dev_warn_once (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kobj_to_dev (struct kobject*) ; 
 int /*<<< orphan*/  nvmem_device_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t,char*) ; 
 int /*<<< orphan*/  nvram_warning ; 

__attribute__((used)) static ssize_t
rtc_nvram_read(struct file *filp, struct kobject *kobj,
	       struct bin_attribute *attr,
	       char *buf, loff_t off, size_t count)
{
	dev_warn_once(kobj_to_dev(kobj), nvram_warning);

	return nvmem_device_read(attr->private, off, count, buf);
}