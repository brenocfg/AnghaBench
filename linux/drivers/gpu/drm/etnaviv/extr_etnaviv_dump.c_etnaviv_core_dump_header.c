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
typedef  void* u32 ;
struct etnaviv_dump_object_header {int file_size; void* file_offset; void* type; void* magic; } ;
struct core_dump_iterator {void* data; void* start; struct etnaviv_dump_object_header* hdr; } ;

/* Variables and functions */
 void* ETDUMP_MAGIC ; 
 void* cpu_to_le32 (void*) ; 

__attribute__((used)) static void etnaviv_core_dump_header(struct core_dump_iterator *iter,
	u32 type, void *data_end)
{
	struct etnaviv_dump_object_header *hdr = iter->hdr;

	hdr->magic = cpu_to_le32(ETDUMP_MAGIC);
	hdr->type = cpu_to_le32(type);
	hdr->file_offset = cpu_to_le32(iter->data - iter->start);
	hdr->file_size = cpu_to_le32(data_end - iter->data);

	iter->hdr++;
	iter->data += hdr->file_size;
}