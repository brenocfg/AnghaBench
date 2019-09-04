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
struct ubi_vtbl_record {int /*<<< orphan*/  crc; } ;
struct ubi_device {int vtbl_slots; int /*<<< orphan*/ * vtbl; } ;

/* Variables and functions */
 int /*<<< orphan*/  UBI_CRC32_INIT ; 
 int /*<<< orphan*/  UBI_VTBL_RECORD_SIZE_CRC ; 
 int /*<<< orphan*/  cpu_to_be32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  crc32 (int /*<<< orphan*/ ,struct ubi_vtbl_record*,int /*<<< orphan*/ ) ; 
 struct ubi_vtbl_record empty_vtbl_record ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,struct ubi_vtbl_record*,int) ; 
 int /*<<< orphan*/  self_vtbl_check (struct ubi_device*) ; 
 int /*<<< orphan*/  ubi_assert (int) ; 
 int ubi_update_layout_vol (struct ubi_device*) ; 

int ubi_change_vtbl_record(struct ubi_device *ubi, int idx,
			   struct ubi_vtbl_record *vtbl_rec)
{
	int err;
	uint32_t crc;

	ubi_assert(idx >= 0 && idx < ubi->vtbl_slots);

	if (!vtbl_rec)
		vtbl_rec = &empty_vtbl_record;
	else {
		crc = crc32(UBI_CRC32_INIT, vtbl_rec, UBI_VTBL_RECORD_SIZE_CRC);
		vtbl_rec->crc = cpu_to_be32(crc);
	}

	memcpy(&ubi->vtbl[idx], vtbl_rec, sizeof(struct ubi_vtbl_record));
	err = ubi_update_layout_vol(ubi);

	self_vtbl_check(ubi);
	return err ? err : 0;
}