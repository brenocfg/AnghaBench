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

/* Variables and functions */
 int ATAPI_MISC ; 
 int ATAPI_PASS_THRU ; 
 int ATAPI_READ ; 
 int ATAPI_READ_CD ; 
 int ATAPI_WRITE ; 
#define  ATA_12 136 
#define  ATA_16 135 
#define  GPCMD_READ_10 134 
#define  GPCMD_READ_12 133 
#define  GPCMD_READ_CD 132 
#define  GPCMD_READ_CD_MSF 131 
#define  GPCMD_WRITE_10 130 
#define  GPCMD_WRITE_12 129 
#define  GPCMD_WRITE_AND_VERIFY_10 128 
 int /*<<< orphan*/  atapi_passthru16 ; 

int atapi_cmd_type(u8 opcode)
{
	switch (opcode) {
	case GPCMD_READ_10:
	case GPCMD_READ_12:
		return ATAPI_READ;

	case GPCMD_WRITE_10:
	case GPCMD_WRITE_12:
	case GPCMD_WRITE_AND_VERIFY_10:
		return ATAPI_WRITE;

	case GPCMD_READ_CD:
	case GPCMD_READ_CD_MSF:
		return ATAPI_READ_CD;

	case ATA_16:
	case ATA_12:
		if (atapi_passthru16)
			return ATAPI_PASS_THRU;
		/* fall thru */
	default:
		return ATAPI_MISC;
	}
}