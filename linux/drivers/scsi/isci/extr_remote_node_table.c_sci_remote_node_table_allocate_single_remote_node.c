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
typedef  int u8 ;
typedef  int u32 ;
typedef  scalar_t__ u16 ;
struct sci_remote_node_table {int dummy; } ;

/* Variables and functions */
 scalar_t__ SCIC_SDS_REMOTE_NODE_CONTEXT_INVALID_INDEX ; 
 int SCIC_SDS_REMOTE_NODE_TABLE_INVALID_INDEX ; 
 int SCU_STP_REMOTE_NODE_COUNT ; 
 int /*<<< orphan*/  sci_remote_node_table_clear_group_index (struct sci_remote_node_table*,int,int) ; 
 int /*<<< orphan*/  sci_remote_node_table_clear_node_index (struct sci_remote_node_table*,scalar_t__) ; 
 int sci_remote_node_table_get_group_index (struct sci_remote_node_table*,int) ; 
 int sci_remote_node_table_get_group_value (struct sci_remote_node_table*,int) ; 
 int /*<<< orphan*/  sci_remote_node_table_set_group_index (struct sci_remote_node_table*,int,int) ; 

__attribute__((used)) static u16 sci_remote_node_table_allocate_single_remote_node(
	struct sci_remote_node_table *remote_node_table,
	u32 group_table_index)
{
	u8 index;
	u8 group_value;
	u32 group_index;
	u16 remote_node_index = SCIC_SDS_REMOTE_NODE_CONTEXT_INVALID_INDEX;

	group_index = sci_remote_node_table_get_group_index(
		remote_node_table, group_table_index);

	/* We could not find an available slot in the table selector 0 */
	if (group_index != SCIC_SDS_REMOTE_NODE_TABLE_INVALID_INDEX) {
		group_value = sci_remote_node_table_get_group_value(
			remote_node_table, group_index);

		for (index = 0; index < SCU_STP_REMOTE_NODE_COUNT; index++) {
			if (((1 << index) & group_value) != 0) {
				/* We have selected a bit now clear it */
				remote_node_index = (u16)(group_index * SCU_STP_REMOTE_NODE_COUNT
							  + index);

				sci_remote_node_table_clear_group_index(
					remote_node_table, group_table_index, group_index
					);

				sci_remote_node_table_clear_node_index(
					remote_node_table, remote_node_index
					);

				if (group_table_index > 0) {
					sci_remote_node_table_set_group_index(
						remote_node_table, group_table_index - 1, group_index
						);
				}

				break;
			}
		}
	}

	return remote_node_index;
}