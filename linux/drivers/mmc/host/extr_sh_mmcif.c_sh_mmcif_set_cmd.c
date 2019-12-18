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
typedef  int u32 ;
struct sh_mmcif_host {int bus_width; int timing; } ;
struct mmc_request {struct mmc_command* cmd; struct mmc_data* data; } ;
struct mmc_data {int blocks; } ;
struct mmc_command {int opcode; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int CMD_SET_CMD12EN ; 
 int CMD_SET_CMLTE ; 
 int CMD_SET_CRC7C_BITS ; 
 int CMD_SET_CRC7C_INTERNAL ; 
 int CMD_SET_DARS ; 
 int CMD_SET_DATW_1 ; 
 int CMD_SET_DATW_4 ; 
 int CMD_SET_DATW_8 ; 
 int CMD_SET_DWEN ; 
 int CMD_SET_RBSY ; 
 int CMD_SET_RIDXC_BITS ; 
 int CMD_SET_RTYP_17B ; 
 int CMD_SET_RTYP_6B ; 
 int CMD_SET_RTYP_NO ; 
 int CMD_SET_WDAT ; 
 int /*<<< orphan*/  MMCIF_CE_BLOCK_SET ; 
 int MMC_ALL_SEND_CID ; 
#define  MMC_BUS_WIDTH_1 136 
#define  MMC_BUS_WIDTH_4 135 
#define  MMC_BUS_WIDTH_8 134 
 int MMC_READ_MULTIPLE_BLOCK ; 
#define  MMC_RSP_NONE 133 
#define  MMC_RSP_R1 132 
#define  MMC_RSP_R1B 131 
#define  MMC_RSP_R2 130 
#define  MMC_RSP_R3 129 
 int MMC_SEND_CID ; 
 int MMC_SEND_CSD ; 
 int MMC_SEND_OP_COND ; 
#define  MMC_TIMING_MMC_DDR52 128 
 int MMC_WRITE_BLOCK ; 
 int MMC_WRITE_MULTIPLE_BLOCK ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 int mmc_resp_type (struct mmc_command*) ; 
 int /*<<< orphan*/  sh_mmcif_bitset (struct sh_mmcif_host*,int /*<<< orphan*/ ,int) ; 
 struct device* sh_mmcif_host_to_dev (struct sh_mmcif_host*) ; 

__attribute__((used)) static u32 sh_mmcif_set_cmd(struct sh_mmcif_host *host,
			    struct mmc_request *mrq)
{
	struct device *dev = sh_mmcif_host_to_dev(host);
	struct mmc_data *data = mrq->data;
	struct mmc_command *cmd = mrq->cmd;
	u32 opc = cmd->opcode;
	u32 tmp = 0;

	/* Response Type check */
	switch (mmc_resp_type(cmd)) {
	case MMC_RSP_NONE:
		tmp |= CMD_SET_RTYP_NO;
		break;
	case MMC_RSP_R1:
	case MMC_RSP_R3:
		tmp |= CMD_SET_RTYP_6B;
		break;
	case MMC_RSP_R1B:
		tmp |= CMD_SET_RBSY | CMD_SET_RTYP_6B;
		break;
	case MMC_RSP_R2:
		tmp |= CMD_SET_RTYP_17B;
		break;
	default:
		dev_err(dev, "Unsupported response type.\n");
		break;
	}

	/* WDAT / DATW */
	if (data) {
		tmp |= CMD_SET_WDAT;
		switch (host->bus_width) {
		case MMC_BUS_WIDTH_1:
			tmp |= CMD_SET_DATW_1;
			break;
		case MMC_BUS_WIDTH_4:
			tmp |= CMD_SET_DATW_4;
			break;
		case MMC_BUS_WIDTH_8:
			tmp |= CMD_SET_DATW_8;
			break;
		default:
			dev_err(dev, "Unsupported bus width.\n");
			break;
		}
		switch (host->timing) {
		case MMC_TIMING_MMC_DDR52:
			/*
			 * MMC core will only set this timing, if the host
			 * advertises the MMC_CAP_1_8V_DDR/MMC_CAP_1_2V_DDR
			 * capability. MMCIF implementations with this
			 * capability, e.g. sh73a0, will have to set it
			 * in their platform data.
			 */
			tmp |= CMD_SET_DARS;
			break;
		}
	}
	/* DWEN */
	if (opc == MMC_WRITE_BLOCK || opc == MMC_WRITE_MULTIPLE_BLOCK)
		tmp |= CMD_SET_DWEN;
	/* CMLTE/CMD12EN */
	if (opc == MMC_READ_MULTIPLE_BLOCK || opc == MMC_WRITE_MULTIPLE_BLOCK) {
		tmp |= CMD_SET_CMLTE | CMD_SET_CMD12EN;
		sh_mmcif_bitset(host, MMCIF_CE_BLOCK_SET,
				data->blocks << 16);
	}
	/* RIDXC[1:0] check bits */
	if (opc == MMC_SEND_OP_COND || opc == MMC_ALL_SEND_CID ||
	    opc == MMC_SEND_CSD || opc == MMC_SEND_CID)
		tmp |= CMD_SET_RIDXC_BITS;
	/* RCRC7C[1:0] check bits */
	if (opc == MMC_SEND_OP_COND)
		tmp |= CMD_SET_CRC7C_BITS;
	/* RCRC7C[1:0] internal CRC7 */
	if (opc == MMC_ALL_SEND_CID ||
		opc == MMC_SEND_CSD || opc == MMC_SEND_CID)
		tmp |= CMD_SET_CRC7C_INTERNAL;

	return (opc << 24) | tmp;
}