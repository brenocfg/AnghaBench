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
struct mmc_command {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
#define  MMC_CMD_AC 136 
#define  MMC_CMD_ADTC 135 
#define  MMC_CMD_BC 134 
#define  MMC_CMD_BCR 133 
#define  MMC_RSP_NONE 132 
#define  MMC_RSP_R1 131 
#define  MMC_RSP_R1B 130 
#define  MMC_RSP_R2 129 
#define  MMC_RSP_R3 128 
 unsigned int TIFM_MMCSD_CMD_AC ; 
 unsigned int TIFM_MMCSD_CMD_ADTC ; 
 unsigned int TIFM_MMCSD_CMD_BC ; 
 unsigned int TIFM_MMCSD_CMD_BCR ; 
 unsigned int TIFM_MMCSD_RSP_BUSY ; 
 unsigned int TIFM_MMCSD_RSP_R0 ; 
 unsigned int TIFM_MMCSD_RSP_R1 ; 
 unsigned int TIFM_MMCSD_RSP_R2 ; 
 unsigned int TIFM_MMCSD_RSP_R3 ; 
 int mmc_cmd_type (struct mmc_command*) ; 
 int mmc_resp_type (struct mmc_command*) ; 

__attribute__((used)) static unsigned int tifm_sd_op_flags(struct mmc_command *cmd)
{
	unsigned int rc = 0;

	switch (mmc_resp_type(cmd)) {
	case MMC_RSP_NONE:
		rc |= TIFM_MMCSD_RSP_R0;
		break;
	case MMC_RSP_R1B:
		rc |= TIFM_MMCSD_RSP_BUSY;
		/* fall-through */
	case MMC_RSP_R1:
		rc |= TIFM_MMCSD_RSP_R1;
		break;
	case MMC_RSP_R2:
		rc |= TIFM_MMCSD_RSP_R2;
		break;
	case MMC_RSP_R3:
		rc |= TIFM_MMCSD_RSP_R3;
		break;
	default:
		BUG();
	}

	switch (mmc_cmd_type(cmd)) {
	case MMC_CMD_BC:
		rc |= TIFM_MMCSD_CMD_BC;
		break;
	case MMC_CMD_BCR:
		rc |= TIFM_MMCSD_CMD_BCR;
		break;
	case MMC_CMD_AC:
		rc |= TIFM_MMCSD_CMD_AC;
		break;
	case MMC_CMD_ADTC:
		rc |= TIFM_MMCSD_CMD_ADTC;
		break;
	default:
		BUG();
	}
	return rc;
}