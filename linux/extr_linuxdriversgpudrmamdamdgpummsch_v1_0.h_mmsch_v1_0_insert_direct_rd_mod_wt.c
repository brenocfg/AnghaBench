#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  void* uint32_t ;
struct TYPE_2__ {void* reg_offset; } ;
struct mmsch_v1_0_cmd_direct_read_modify_write {void* write_data; void* mask_value; TYPE_1__ cmd_header; } ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (void*,struct mmsch_v1_0_cmd_direct_read_modify_write*,int) ; 

__attribute__((used)) static inline void mmsch_v1_0_insert_direct_rd_mod_wt(struct mmsch_v1_0_cmd_direct_read_modify_write *direct_rd_mod_wt,
						      uint32_t *init_table,
						      uint32_t reg_offset,
						      uint32_t mask, uint32_t data)
{
	direct_rd_mod_wt->cmd_header.reg_offset = reg_offset;
	direct_rd_mod_wt->mask_value = mask;
	direct_rd_mod_wt->write_data = data;
	memcpy((void *)init_table, direct_rd_mod_wt,
	       sizeof(struct mmsch_v1_0_cmd_direct_read_modify_write));
}