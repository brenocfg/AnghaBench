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
typedef  int u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct TYPE_2__ {void* flags; void* type; } ;
struct r5l_payload_data_parity {void** checksum; int /*<<< orphan*/  location; void* size; TYPE_1__ header; } ;
struct r5l_log {struct r5l_io_unit* current_io; } ;
struct r5l_io_unit {int meta_offset; int /*<<< orphan*/  meta_page; } ;
typedef  int /*<<< orphan*/  sector_t ;
typedef  int /*<<< orphan*/  __le32 ;

/* Variables and functions */
 int PAGE_SHIFT ; 
 void* cpu_to_le16 (int /*<<< orphan*/ ) ; 
 void* cpu_to_le32 (int) ; 
 int /*<<< orphan*/  cpu_to_le64 (int /*<<< orphan*/ ) ; 
 struct r5l_payload_data_parity* page_address (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void r5l_append_payload_meta(struct r5l_log *log, u16 type,
				    sector_t location,
				    u32 checksum1, u32 checksum2,
				    bool checksum2_valid)
{
	struct r5l_io_unit *io = log->current_io;
	struct r5l_payload_data_parity *payload;

	payload = page_address(io->meta_page) + io->meta_offset;
	payload->header.type = cpu_to_le16(type);
	payload->header.flags = cpu_to_le16(0);
	payload->size = cpu_to_le32((1 + !!checksum2_valid) <<
				    (PAGE_SHIFT - 9));
	payload->location = cpu_to_le64(location);
	payload->checksum[0] = cpu_to_le32(checksum1);
	if (checksum2_valid)
		payload->checksum[1] = cpu_to_le32(checksum2);

	io->meta_offset += sizeof(struct r5l_payload_data_parity) +
		sizeof(__le32) * (1 + !!checksum2_valid);
}