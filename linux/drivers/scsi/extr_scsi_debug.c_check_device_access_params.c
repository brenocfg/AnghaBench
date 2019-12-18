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
struct scsi_cmnd {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DATA_PROTECT ; 
 int /*<<< orphan*/  ILLEGAL_REQUEST ; 
 int /*<<< orphan*/  INVALID_FIELD_IN_CDB ; 
 int /*<<< orphan*/  LBA_OUT_OF_RANGE ; 
 int /*<<< orphan*/  WRITE_PROTECTED ; 
 int check_condition_result ; 
 int /*<<< orphan*/  mk_sense_buffer (struct scsi_cmnd*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 unsigned long long sdebug_capacity ; 
 unsigned int sdebug_store_sectors ; 
 int /*<<< orphan*/  sdebug_wp ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int check_device_access_params(struct scsi_cmnd *scp,
	unsigned long long lba, unsigned int num, bool write)
{
	if (lba + num > sdebug_capacity) {
		mk_sense_buffer(scp, ILLEGAL_REQUEST, LBA_OUT_OF_RANGE, 0);
		return check_condition_result;
	}
	/* transfer length excessive (tie in to block limits VPD page) */
	if (num > sdebug_store_sectors) {
		/* needs work to find which cdb byte 'num' comes from */
		mk_sense_buffer(scp, ILLEGAL_REQUEST, INVALID_FIELD_IN_CDB, 0);
		return check_condition_result;
	}
	if (write && unlikely(sdebug_wp)) {
		mk_sense_buffer(scp, DATA_PROTECT, WRITE_PROTECTED, 0x2);
		return check_condition_result;
	}
	return 0;
}