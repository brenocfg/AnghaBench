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
 int EINVAL ; 
#define  MMC_RSP_NONE 133 
#define  MMC_RSP_R1 132 
#define  MMC_RSP_R1B 131 
#define  MMC_RSP_R1_NO_CRC 130 
#define  MMC_RSP_R2 129 
#define  MMC_RSP_R3 128 
 int SD_NO_CHECK_CRC7 ; 
 int SD_RSP_TYPE_R0 ; 
 int SD_RSP_TYPE_R1 ; 
 int SD_RSP_TYPE_R1b ; 
 int SD_RSP_TYPE_R2 ; 
 int SD_RSP_TYPE_R3 ; 
 int mmc_resp_type (struct mmc_command*) ; 

__attribute__((used)) static int sd_response_type(struct mmc_command *cmd)
{
	switch (mmc_resp_type(cmd)) {
	case MMC_RSP_NONE:
		return SD_RSP_TYPE_R0;
	case MMC_RSP_R1:
		return SD_RSP_TYPE_R1;
	case MMC_RSP_R1_NO_CRC:
		return SD_RSP_TYPE_R1 | SD_NO_CHECK_CRC7;
	case MMC_RSP_R1B:
		return SD_RSP_TYPE_R1b;
	case MMC_RSP_R2:
		return SD_RSP_TYPE_R2;
	case MMC_RSP_R3:
		return SD_RSP_TYPE_R3;
	default:
		return -EINVAL;
	}
}