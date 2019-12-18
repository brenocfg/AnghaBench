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
typedef  int u64 ;
struct core_table_entry {int type; int offset; int length; int s2c_dma_present; int s2c_dma_channel_num; int c2s_dma_present; int c2s_dma_channel_num; int irq_count; int irq_base_num; } ;

/* Variables and functions */

__attribute__((used)) static
void  parse_core_table_entry_v0(struct core_table_entry *cte, const u64 read_val)
{
	cte->type                = ((read_val & 0xFFF0000000000000UL) >> 52);
	cte->offset              = ((read_val & 0x00000000FFFF0000UL) >> 16) * 4096;
	cte->length              = ((read_val & 0x0000FFFF00000000UL) >> 32) * 8;
	cte->s2c_dma_present     = ((read_val & 0x0008000000000000UL) >> 51);
	cte->s2c_dma_channel_num = ((read_val & 0x0007000000000000UL) >> 48);
	cte->c2s_dma_present     = ((read_val & 0x0000000000008000UL) >> 15);
	cte->c2s_dma_channel_num = ((read_val & 0x0000000000007000UL) >> 12);
	cte->irq_count           = ((read_val & 0x0000000000000C00UL) >> 10);
	cte->irq_base_num        = ((read_val & 0x00000000000003F8UL) >>  3);
}