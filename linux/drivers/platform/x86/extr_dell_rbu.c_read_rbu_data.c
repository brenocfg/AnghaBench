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
struct bin_attribute {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;
typedef  int /*<<< orphan*/  loff_t ;
struct TYPE_2__ {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  image_type ; 
 int /*<<< orphan*/  pr_debug (char*) ; 
 TYPE_1__ rbu_data ; 
 int /*<<< orphan*/  read_packet_data (char*,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  read_rbu_mono_data (char*,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static ssize_t read_rbu_data(struct file *filp, struct kobject *kobj,
			     struct bin_attribute *bin_attr,
			     char *buffer, loff_t pos, size_t count)
{
	ssize_t ret_count = 0;

	spin_lock(&rbu_data.lock);

	if (!strcmp(image_type, "mono"))
		ret_count = read_rbu_mono_data(buffer, pos, count);
	else if (!strcmp(image_type, "packet"))
		ret_count = read_packet_data(buffer, pos, count);
	else
		pr_debug("read_rbu_data: invalid image type specified\n");

	spin_unlock(&rbu_data.lock);
	return ret_count;
}