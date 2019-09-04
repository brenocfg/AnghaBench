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
struct memory_block {int /*<<< orphan*/  section_count; int /*<<< orphan*/  dev; } ;
struct mem_section {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MEM_OFFLINE ; 
 struct memory_block* find_memory_block (struct mem_section*) ; 
 int init_memory_block (struct memory_block**,struct mem_section*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mem_sysfs_mutex ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  put_device (int /*<<< orphan*/ *) ; 

int hotplug_memory_register(int nid, struct mem_section *section)
{
	int ret = 0;
	struct memory_block *mem;

	mutex_lock(&mem_sysfs_mutex);

	mem = find_memory_block(section);
	if (mem) {
		mem->section_count++;
		put_device(&mem->dev);
	} else {
		ret = init_memory_block(&mem, section, MEM_OFFLINE);
		if (ret)
			goto out;
		mem->section_count++;
	}

out:
	mutex_unlock(&mem_sysfs_mutex);
	return ret;
}