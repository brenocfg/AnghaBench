#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct kobject {int dummy; } ;
struct file {int dummy; } ;
struct bin_attribute {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;
typedef  int /*<<< orphan*/  loff_t ;
struct TYPE_4__ {int /*<<< orphan*/  len; } ;
struct TYPE_5__ {TYPE_1__ hdr; } ;

/* Variables and functions */
 TYPE_2__ ipl_block ; 
 int /*<<< orphan*/  memory_read_from_buffer (char*,size_t,int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static ssize_t ipl_parameter_read(struct file *filp, struct kobject *kobj,
				  struct bin_attribute *attr, char *buf,
				  loff_t off, size_t count)
{
	return memory_read_from_buffer(buf, count, &off, &ipl_block,
				       ipl_block.hdr.len);
}