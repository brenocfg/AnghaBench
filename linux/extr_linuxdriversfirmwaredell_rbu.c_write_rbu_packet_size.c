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
typedef  size_t ssize_t ;
typedef  int /*<<< orphan*/  loff_t ;
struct TYPE_2__ {unsigned long packetsize; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  packet_empty_list () ; 
 TYPE_1__ rbu_data ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sscanf (char*,char*,unsigned long*) ; 

__attribute__((used)) static ssize_t write_rbu_packet_size(struct file *filp, struct kobject *kobj,
				     struct bin_attribute *bin_attr,
				     char *buffer, loff_t pos, size_t count)
{
	unsigned long temp;
	spin_lock(&rbu_data.lock);
	packet_empty_list();
	sscanf(buffer, "%lu", &temp);
	if (temp < 0xffffffff)
		rbu_data.packetsize = temp;

	spin_unlock(&rbu_data.lock);
	return count;
}