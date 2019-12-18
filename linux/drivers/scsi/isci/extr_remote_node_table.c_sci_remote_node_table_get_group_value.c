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
typedef  int /*<<< orphan*/  u8 ;
typedef  size_t u32 ;
struct sci_remote_node_table {size_t* available_remote_nodes; } ;

/* Variables and functions */
 size_t SCIC_SDS_REMOTE_NODE_SETS_PER_DWORD ; 
 size_t SCIC_SDS_REMOTE_NODE_TABLE_FULL_SLOT_VALUE ; 

__attribute__((used)) static u8 sci_remote_node_table_get_group_value(
	struct sci_remote_node_table *remote_node_table,
	u32 group_index)
{
	u32 dword_location;
	u32 dword_remainder;
	u32 dword_value;

	dword_location  = group_index / SCIC_SDS_REMOTE_NODE_SETS_PER_DWORD;
	dword_remainder = group_index % SCIC_SDS_REMOTE_NODE_SETS_PER_DWORD;

	dword_value = remote_node_table->available_remote_nodes[dword_location];
	dword_value &= (SCIC_SDS_REMOTE_NODE_TABLE_FULL_SLOT_VALUE << (dword_remainder * 4));
	dword_value = dword_value >> (dword_remainder * 4);

	return (u8)dword_value;
}