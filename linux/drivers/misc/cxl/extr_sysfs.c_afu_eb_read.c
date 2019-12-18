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
struct kobject {int dummy; } ;
struct file {int dummy; } ;
struct cxl_afu {int dummy; } ;
struct bin_attribute {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;
typedef  int /*<<< orphan*/  loff_t ;
struct TYPE_2__ {int /*<<< orphan*/  (* afu_read_err_buffer ) (struct cxl_afu*,char*,int /*<<< orphan*/ ,size_t) ;} ;

/* Variables and functions */
 TYPE_1__* cxl_ops ; 
 int /*<<< orphan*/  kobj_to_dev (struct kobject*) ; 
 int /*<<< orphan*/  stub1 (struct cxl_afu*,char*,int /*<<< orphan*/ ,size_t) ; 
 struct cxl_afu* to_cxl_afu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static ssize_t afu_eb_read(struct file *filp, struct kobject *kobj,
			       struct bin_attribute *bin_attr, char *buf,
			       loff_t off, size_t count)
{
	struct cxl_afu *afu = to_cxl_afu(kobj_to_dev(kobj));

	return cxl_ops->afu_read_err_buffer(afu, buf, off, count);
}