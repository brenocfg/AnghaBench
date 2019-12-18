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
typedef  int u32 ;
struct sci_remote_node_table {int group_array_size; int** remote_node_groups; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int SCU_STP_REMOTE_NODE_COUNT ; 

__attribute__((used)) static void sci_remote_node_table_clear_group_index(
	struct sci_remote_node_table *remote_node_table,
	u32 group_table_index,
	u32 group_index)
{
	u32 dword_index;
	u32 bit_index;
	u32 *group_table;

	BUG_ON(group_table_index >= SCU_STP_REMOTE_NODE_COUNT);
	BUG_ON(group_index >= (u32)(remote_node_table->group_array_size * 32));

	dword_index = group_index / 32;
	bit_index   = group_index % 32;
	group_table = remote_node_table->remote_node_groups[group_table_index];

	group_table[dword_index] = group_table[dword_index] & ~(1 << bit_index);
}