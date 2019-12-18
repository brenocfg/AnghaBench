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
struct dbg_tools_data {int chip_id; } ;
struct qed_hwfn {struct dbg_tools_data dbg_info; } ;
struct dbg_bus_block {int dummy; } ;
typedef  enum block_id { ____Placeholder_block_id } block_id ;

/* Variables and functions */
 int MAX_CHIP_IDS ; 
 int /*<<< orphan*/ * dbg_bus_blocks ; 

__attribute__((used)) static struct dbg_bus_block *get_dbg_bus_block_desc(struct qed_hwfn *p_hwfn,
						    enum block_id block_id)
{
	struct dbg_tools_data *dev_data = &p_hwfn->dbg_info;

	return (struct dbg_bus_block *)&dbg_bus_blocks[block_id *
						       MAX_CHIP_IDS +
						       dev_data->chip_id];
}