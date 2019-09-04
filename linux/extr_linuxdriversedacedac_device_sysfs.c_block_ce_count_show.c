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
struct TYPE_2__ {int ce_count; } ;
struct edac_device_block {TYPE_1__ counters; } ;
struct attribute {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 
 struct edac_device_block* to_block (struct kobject*) ; 

__attribute__((used)) static ssize_t block_ce_count_show(struct kobject *kobj,
					struct attribute *attr, char *data)
{
	struct edac_device_block *block = to_block(kobj);

	return sprintf(data, "%u\n", block->counters.ce_count);
}