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
typedef  int /*<<< orphan*/  uint32_t ;
struct amdgpu_ras_eeprom_table_header {void* checksum; void* tbl_size; void* first_rec_offset; void* version; void* header; } ;

/* Variables and functions */
 void* le32_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void __decode_table_header_from_buff(struct amdgpu_ras_eeprom_table_header *hdr,
					  unsigned char *buff)
{
	uint32_t *pp = (uint32_t *)buff;

	hdr->header 	      = le32_to_cpu(pp[0]);
	hdr->version 	      = le32_to_cpu(pp[1]);
	hdr->first_rec_offset = le32_to_cpu(pp[2]);
	hdr->tbl_size 	      = le32_to_cpu(pp[3]);
	hdr->checksum 	      = le32_to_cpu(pp[4]);
}