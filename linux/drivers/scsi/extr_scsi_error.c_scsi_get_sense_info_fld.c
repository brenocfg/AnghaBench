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
typedef  int /*<<< orphan*/  u64 ;

/* Variables and functions */
 int /*<<< orphan*/  get_unaligned_be32 (int const*) ; 
 int /*<<< orphan*/  get_unaligned_be64 (int const*) ; 
 int* scsi_sense_desc_find (int const*,int,int /*<<< orphan*/ ) ; 

bool scsi_get_sense_info_fld(const u8 *sense_buffer, int sb_len,
			     u64 *info_out)
{
	const u8 * ucp;

	if (sb_len < 7)
		return false;
	switch (sense_buffer[0] & 0x7f) {
	case 0x70:
	case 0x71:
		if (sense_buffer[0] & 0x80) {
			*info_out = get_unaligned_be32(&sense_buffer[3]);
			return true;
		}
		return false;
	case 0x72:
	case 0x73:
		ucp = scsi_sense_desc_find(sense_buffer, sb_len,
					   0 /* info desc */);
		if (ucp && (0xa == ucp[1])) {
			*info_out = get_unaligned_be64(&ucp[4]);
			return true;
		}
		return false;
	default:
		return false;
	}
}