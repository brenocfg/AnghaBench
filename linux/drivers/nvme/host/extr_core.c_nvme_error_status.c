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
typedef  int u16 ;
typedef  int /*<<< orphan*/  blk_status_t ;

/* Variables and functions */
 int /*<<< orphan*/  BLK_STS_IOERR ; 
 int /*<<< orphan*/  BLK_STS_MEDIUM ; 
 int /*<<< orphan*/  BLK_STS_NEXUS ; 
 int /*<<< orphan*/  BLK_STS_NOSPC ; 
 int /*<<< orphan*/  BLK_STS_NOTSUPP ; 
 int /*<<< orphan*/  BLK_STS_OK ; 
 int /*<<< orphan*/  BLK_STS_PROTECTION ; 
 int /*<<< orphan*/  BLK_STS_TARGET ; 
 int /*<<< orphan*/  BLK_STS_TRANSPORT ; 
#define  NVME_SC_ACCESS_DENIED 147 
#define  NVME_SC_APPTAG_CHECK 146 
#define  NVME_SC_BAD_ATTRIBUTES 145 
#define  NVME_SC_CAP_EXCEEDED 144 
#define  NVME_SC_COMPARE_FAILED 143 
#define  NVME_SC_GUARD_CHECK 142 
#define  NVME_SC_HOST_PATH_ERROR 141 
#define  NVME_SC_INVALID_FIELD 140 
#define  NVME_SC_INVALID_NS 139 
#define  NVME_SC_INVALID_OPCODE 138 
#define  NVME_SC_INVALID_PI 137 
#define  NVME_SC_LBA_RANGE 136 
#define  NVME_SC_ONCS_NOT_SUPPORTED 135 
#define  NVME_SC_READ_ERROR 134 
#define  NVME_SC_READ_ONLY 133 
#define  NVME_SC_REFTAG_CHECK 132 
#define  NVME_SC_RESERVATION_CONFLICT 131 
#define  NVME_SC_SUCCESS 130 
#define  NVME_SC_UNWRITTEN_BLOCK 129 
#define  NVME_SC_WRITE_FAULT 128 

__attribute__((used)) static blk_status_t nvme_error_status(u16 status)
{
	switch (status & 0x7ff) {
	case NVME_SC_SUCCESS:
		return BLK_STS_OK;
	case NVME_SC_CAP_EXCEEDED:
		return BLK_STS_NOSPC;
	case NVME_SC_LBA_RANGE:
		return BLK_STS_TARGET;
	case NVME_SC_BAD_ATTRIBUTES:
	case NVME_SC_ONCS_NOT_SUPPORTED:
	case NVME_SC_INVALID_OPCODE:
	case NVME_SC_INVALID_FIELD:
	case NVME_SC_INVALID_NS:
		return BLK_STS_NOTSUPP;
	case NVME_SC_WRITE_FAULT:
	case NVME_SC_READ_ERROR:
	case NVME_SC_UNWRITTEN_BLOCK:
	case NVME_SC_ACCESS_DENIED:
	case NVME_SC_READ_ONLY:
	case NVME_SC_COMPARE_FAILED:
		return BLK_STS_MEDIUM;
	case NVME_SC_GUARD_CHECK:
	case NVME_SC_APPTAG_CHECK:
	case NVME_SC_REFTAG_CHECK:
	case NVME_SC_INVALID_PI:
		return BLK_STS_PROTECTION;
	case NVME_SC_RESERVATION_CONFLICT:
		return BLK_STS_NEXUS;
	case NVME_SC_HOST_PATH_ERROR:
		return BLK_STS_TRANSPORT;
	default:
		return BLK_STS_IOERR;
	}
}