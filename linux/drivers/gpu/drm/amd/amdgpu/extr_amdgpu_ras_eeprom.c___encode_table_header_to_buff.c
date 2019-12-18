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
struct amdgpu_ras_eeprom_table_header {int /*<<< orphan*/  checksum; int /*<<< orphan*/  tbl_size; int /*<<< orphan*/  first_rec_offset; int /*<<< orphan*/  version; int /*<<< orphan*/  header; } ;

/* Variables and functions */
 int /*<<< orphan*/  cpu_to_le32 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void __encode_table_header_to_buff(struct amdgpu_ras_eeprom_table_header *hdr,
					  unsigned char *buff)
{
	uint32_t *pp = (uint32_t *) buff;

	pp[0] = cpu_to_le32(hdr->header);
	pp[1] = cpu_to_le32(hdr->version);
	pp[2] = cpu_to_le32(hdr->first_rec_offset);
	pp[3] = cpu_to_le32(hdr->tbl_size);
	pp[4] = cpu_to_le32(hdr->checksum);
}