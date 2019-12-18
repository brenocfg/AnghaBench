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
typedef  int /*<<< orphan*/  u8 ;
struct scsi_cmnd {int* cmnd; } ;

/* Variables and functions */
 int /*<<< orphan*/  SD_RSP_TYPE_R0 ; 
 int /*<<< orphan*/  SD_RSP_TYPE_R1 ; 
 int /*<<< orphan*/  SD_RSP_TYPE_R1b ; 
 int /*<<< orphan*/  SD_RSP_TYPE_R2 ; 
 int /*<<< orphan*/  SD_RSP_TYPE_R3 ; 
 int STATUS_FAIL ; 
 int STATUS_SUCCESS ; 

__attribute__((used)) static inline int get_rsp_type(struct scsi_cmnd *srb, u8 *rsp_type,
			       int *rsp_len)
{
	if (!rsp_type || !rsp_len)
		return STATUS_FAIL;

	switch (srb->cmnd[10]) {
	case 0x03:
		*rsp_type = SD_RSP_TYPE_R0;
		*rsp_len = 0;
		break;

	case 0x04:
		*rsp_type = SD_RSP_TYPE_R1;
		*rsp_len = 6;
		break;

	case 0x05:
		*rsp_type = SD_RSP_TYPE_R1b;
		*rsp_len = 6;
		break;

	case 0x06:
		*rsp_type = SD_RSP_TYPE_R2;
		*rsp_len = 17;
		break;

	case 0x07:
		*rsp_type = SD_RSP_TYPE_R3;
		*rsp_len = 6;
		break;

	default:
		return STATUS_FAIL;
	}

	return STATUS_SUCCESS;
}