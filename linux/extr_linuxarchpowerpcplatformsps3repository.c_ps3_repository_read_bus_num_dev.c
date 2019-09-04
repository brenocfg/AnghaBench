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
typedef  unsigned int u64 ;

/* Variables and functions */
 int /*<<< orphan*/  PS3_LPAR_ID_PME ; 
 int /*<<< orphan*/  make_field (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  make_first_field (char*,unsigned int) ; 
 int read_node (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int*,int /*<<< orphan*/ *) ; 

int ps3_repository_read_bus_num_dev(unsigned int bus_index,
	unsigned int *num_dev)
{
	int result;
	u64 v1 = 0;

	result = read_node(PS3_LPAR_ID_PME,
		make_first_field("bus", bus_index),
		make_field("num_dev", 0),
		0, 0,
		&v1, NULL);
	*num_dev = v1;
	return result;
}