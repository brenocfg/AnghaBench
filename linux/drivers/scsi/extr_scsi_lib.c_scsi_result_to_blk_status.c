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
typedef  int /*<<< orphan*/  blk_status_t ;

/* Variables and functions */
 int /*<<< orphan*/  BLK_STS_IOERR ; 
 int /*<<< orphan*/  BLK_STS_MEDIUM ; 
 int /*<<< orphan*/  BLK_STS_NEXUS ; 
 int /*<<< orphan*/  BLK_STS_NOSPC ; 
 int /*<<< orphan*/  BLK_STS_OK ; 
 int /*<<< orphan*/  BLK_STS_TARGET ; 
 int /*<<< orphan*/  BLK_STS_TRANSPORT ; 
#define  DID_ALLOC_FAILURE 133 
#define  DID_MEDIUM_ERROR 132 
#define  DID_NEXUS_FAILURE 131 
#define  DID_OK 130 
#define  DID_TARGET_FAILURE 129 
#define  DID_TRANSPORT_FAILFAST 128 
 int host_byte (int) ; 
 int /*<<< orphan*/  scsi_status_is_good (int) ; 
 int /*<<< orphan*/  set_host_byte (struct scsi_cmnd*,int const) ; 

__attribute__((used)) static blk_status_t scsi_result_to_blk_status(struct scsi_cmnd *cmd, int result)
{
	switch (host_byte(result)) {
	case DID_OK:
		/*
		 * Also check the other bytes than the status byte in result
		 * to handle the case when a SCSI LLD sets result to
		 * DRIVER_SENSE << 24 without setting SAM_STAT_CHECK_CONDITION.
		 */
		if (scsi_status_is_good(result) && (result & ~0xff) == 0)
			return BLK_STS_OK;
		return BLK_STS_IOERR;
	case DID_TRANSPORT_FAILFAST:
		return BLK_STS_TRANSPORT;
	case DID_TARGET_FAILURE:
		set_host_byte(cmd, DID_OK);
		return BLK_STS_TARGET;
	case DID_NEXUS_FAILURE:
		set_host_byte(cmd, DID_OK);
		return BLK_STS_NEXUS;
	case DID_ALLOC_FAILURE:
		set_host_byte(cmd, DID_OK);
		return BLK_STS_NOSPC;
	case DID_MEDIUM_ERROR:
		set_host_byte(cmd, DID_OK);
		return BLK_STS_MEDIUM;
	default:
		return BLK_STS_IOERR;
	}
}