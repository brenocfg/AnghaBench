#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__ global_mmio_size; } ;
struct ocxl_afu {scalar_t__ global_mmio_ptr; TYPE_1__ config; } ;
struct kobject {int dummy; } ;
struct file {int dummy; } ;
struct bin_attribute {int dummy; } ;
typedef  size_t ssize_t ;
typedef  scalar_t__ loff_t ;

/* Variables and functions */
 int /*<<< orphan*/  kobj_to_dev (struct kobject*) ; 
 int /*<<< orphan*/  memcpy_fromio (char*,scalar_t__,size_t) ; 
 struct ocxl_afu* to_afu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static ssize_t global_mmio_read(struct file *filp, struct kobject *kobj,
				struct bin_attribute *bin_attr, char *buf,
				loff_t off, size_t count)
{
	struct ocxl_afu *afu = to_afu(kobj_to_dev(kobj));

	if (count == 0 || off < 0 ||
		off >= afu->config.global_mmio_size)
		return 0;
	memcpy_fromio(buf, afu->global_mmio_ptr + off, count);
	return count;
}