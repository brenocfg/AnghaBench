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
typedef  scalar_t__ u32 ;
struct sdebug_dev_info {int dummy; } ;
struct scsi_cmnd {int* cmnd; } ;

/* Variables and functions */
 int /*<<< orphan*/  SDEB_IN_CDB ; 
 int check_condition_result ; 
 scalar_t__ get_unaligned_be32 (int*) ; 
 int /*<<< orphan*/  get_unaligned_be64 (int*) ; 
 int /*<<< orphan*/  mk_sense_invalid_fld (struct scsi_cmnd*,int /*<<< orphan*/ ,int,int) ; 
 int resp_write_same (struct scsi_cmnd*,int /*<<< orphan*/ ,scalar_t__,scalar_t__,int,int) ; 
 scalar_t__ sdebug_lbpws ; 
 scalar_t__ sdebug_write_same_length ; 

__attribute__((used)) static int resp_write_same_16(struct scsi_cmnd *scp,
			      struct sdebug_dev_info *devip)
{
	u8 *cmd = scp->cmnd;
	u64 lba;
	u32 num;
	u32 ei_lba = 0;
	bool unmap = false;
	bool ndob = false;

	if (cmd[1] & 0x8) {	/* UNMAP */
		if (sdebug_lbpws == 0) {
			mk_sense_invalid_fld(scp, SDEB_IN_CDB, 1, 3);
			return check_condition_result;
		} else
			unmap = true;
	}
	if (cmd[1] & 0x1)  /* NDOB (no data-out buffer, assumes zeroes) */
		ndob = true;
	lba = get_unaligned_be64(cmd + 2);
	num = get_unaligned_be32(cmd + 10);
	if (num > sdebug_write_same_length) {
		mk_sense_invalid_fld(scp, SDEB_IN_CDB, 10, -1);
		return check_condition_result;
	}
	return resp_write_same(scp, lba, num, ei_lba, unmap, ndob);
}