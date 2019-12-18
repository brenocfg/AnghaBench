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
typedef  scalar_t__ u32 ;
typedef  int u16 ;
struct sci_remote_node_table {int dummy; } ;

/* Variables and functions */
 int SCIC_SDS_REMOTE_NODE_CONTEXT_INVALID_INDEX ; 
 scalar_t__ SCIC_SDS_REMOTE_NODE_TABLE_INVALID_INDEX ; 
 int SCU_STP_REMOTE_NODE_COUNT ; 
 int /*<<< orphan*/  sci_remote_node_table_clear_group (struct sci_remote_node_table*,scalar_t__) ; 
 int /*<<< orphan*/  sci_remote_node_table_clear_group_index (struct sci_remote_node_table*,scalar_t__,scalar_t__) ; 
 scalar_t__ sci_remote_node_table_get_group_index (struct sci_remote_node_table*,scalar_t__) ; 

__attribute__((used)) static u16 sci_remote_node_table_allocate_triple_remote_node(
	struct sci_remote_node_table *remote_node_table,
	u32 group_table_index)
{
	u32 group_index;
	u16 remote_node_index = SCIC_SDS_REMOTE_NODE_CONTEXT_INVALID_INDEX;

	group_index = sci_remote_node_table_get_group_index(
		remote_node_table, group_table_index);

	if (group_index != SCIC_SDS_REMOTE_NODE_TABLE_INVALID_INDEX) {
		remote_node_index = (u16)group_index * SCU_STP_REMOTE_NODE_COUNT;

		sci_remote_node_table_clear_group_index(
			remote_node_table, group_table_index, group_index
			);

		sci_remote_node_table_clear_group(
			remote_node_table, group_index
			);
	}

	return remote_node_index;
}