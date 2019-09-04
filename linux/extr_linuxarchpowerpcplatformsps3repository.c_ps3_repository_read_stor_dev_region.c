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
typedef  int /*<<< orphan*/  u64 ;

/* Variables and functions */
 int ps3_repository_read_stor_dev_region_id (unsigned int,unsigned int,unsigned int,unsigned int*) ; 
 int ps3_repository_read_stor_dev_region_size (unsigned int,unsigned int,unsigned int,int /*<<< orphan*/ *) ; 
 int ps3_repository_read_stor_dev_region_start (unsigned int,unsigned int,unsigned int,int /*<<< orphan*/ *) ; 

int ps3_repository_read_stor_dev_region(unsigned int bus_index,
	unsigned int dev_index, unsigned int region_index,
	unsigned int *region_id, u64 *region_start, u64 *region_size)
{
	int result;

	result = ps3_repository_read_stor_dev_region_id(bus_index, dev_index,
		region_index, region_id);
	if (result)
	    return result;

	result = ps3_repository_read_stor_dev_region_start(bus_index, dev_index,
		region_index, region_start);
	if (result)
	    return result;

	result = ps3_repository_read_stor_dev_region_size(bus_index, dev_index,
		region_index, region_size);
	return result;
}