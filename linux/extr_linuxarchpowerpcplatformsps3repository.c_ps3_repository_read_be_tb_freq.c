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
typedef  scalar_t__ u64 ;

/* Variables and functions */
 int ps3_repository_read_be_node_id (unsigned int,scalar_t__*) ; 
 int ps3_repository_read_tb_freq (scalar_t__,scalar_t__*) ; 

int ps3_repository_read_be_tb_freq(unsigned int be_index, u64 *tb_freq)
{
	int result;
	u64 node_id;

	*tb_freq = 0;
	result = ps3_repository_read_be_node_id(be_index, &node_id);
	return result ? result
		: ps3_repository_read_tb_freq(node_id, tb_freq);
}