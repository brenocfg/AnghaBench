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
typedef  int /*<<< orphan*/  loff_t ;

/* Variables and functions */
 int /*<<< orphan*/  opal_msglog_copy (char*,int /*<<< orphan*/ ,size_t) ; 

__attribute__((used)) static ssize_t opal_msglog_read(struct file *file, struct kobject *kobj,
				struct bin_attribute *bin_attr, char *to,
				loff_t pos, size_t count)
{
	return opal_msglog_copy(to, pos, count);
}