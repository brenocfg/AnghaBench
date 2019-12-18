#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {void* controller_function; void* controller_number; void* implemented_capacity; void* memory_device_code; void* memory_manufacturer_code; void* page_size; void* number_of_effective_blocks; void* number_of_blocks; void* block_size; } ;
struct TYPE_8__ {void* data_size; void* start_addr; } ;
struct TYPE_7__ {void* data_size; void* start_addr; } ;
struct TYPE_9__ {TYPE_3__ cis_idi; TYPE_2__ disabled_block; } ;
struct TYPE_6__ {void* format_reserved; void* block_id; } ;
struct ms_boot_page {TYPE_5__ attr; TYPE_4__ entry; TYPE_1__ header; } ;

/* Variables and functions */
 void* be16_to_cpu (void*) ; 
 void* be32_to_cpu (void*) ; 

__attribute__((used)) static void msb_fix_boot_page_endianness(struct ms_boot_page *p)
{
	p->header.block_id = be16_to_cpu(p->header.block_id);
	p->header.format_reserved = be16_to_cpu(p->header.format_reserved);
	p->entry.disabled_block.start_addr
		= be32_to_cpu(p->entry.disabled_block.start_addr);
	p->entry.disabled_block.data_size
		= be32_to_cpu(p->entry.disabled_block.data_size);
	p->entry.cis_idi.start_addr
		= be32_to_cpu(p->entry.cis_idi.start_addr);
	p->entry.cis_idi.data_size
		= be32_to_cpu(p->entry.cis_idi.data_size);
	p->attr.block_size = be16_to_cpu(p->attr.block_size);
	p->attr.number_of_blocks = be16_to_cpu(p->attr.number_of_blocks);
	p->attr.number_of_effective_blocks
		= be16_to_cpu(p->attr.number_of_effective_blocks);
	p->attr.page_size = be16_to_cpu(p->attr.page_size);
	p->attr.memory_manufacturer_code
		= be16_to_cpu(p->attr.memory_manufacturer_code);
	p->attr.memory_device_code = be16_to_cpu(p->attr.memory_device_code);
	p->attr.implemented_capacity
		= be16_to_cpu(p->attr.implemented_capacity);
	p->attr.controller_number = be16_to_cpu(p->attr.controller_number);
	p->attr.controller_function = be16_to_cpu(p->attr.controller_function);
}