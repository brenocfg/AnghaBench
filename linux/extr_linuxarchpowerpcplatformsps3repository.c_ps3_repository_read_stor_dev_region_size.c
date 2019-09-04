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
 int /*<<< orphan*/  PS3_LPAR_ID_PME ; 
 int /*<<< orphan*/  make_field (char*,unsigned int) ; 
 int /*<<< orphan*/  make_first_field (char*,unsigned int) ; 
 int read_node (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int ps3_repository_read_stor_dev_region_size(unsigned int bus_index,
	unsigned int dev_index,	unsigned int region_index, u64 *region_size)
{
	return read_node(PS3_LPAR_ID_PME,
	    make_first_field("bus", bus_index),
	    make_field("dev", dev_index),
	    make_field("region", region_index),
	    make_field("size", 0),
	    region_size, NULL);
}