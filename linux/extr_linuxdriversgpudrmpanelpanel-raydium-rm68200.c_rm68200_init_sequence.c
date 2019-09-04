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
struct rm68200 {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GOA_BICLK1 ; 
 int /*<<< orphan*/  GOA_BICLK2 ; 
 int /*<<< orphan*/  GOA_BICLK3 ; 
 int /*<<< orphan*/  GOA_BICLK4 ; 
 int /*<<< orphan*/  GOA_BICLK_OPT1 ; 
 int /*<<< orphan*/  GOA_BICLK_OPT2 ; 
 int /*<<< orphan*/  GOA_VCLK1 ; 
 int /*<<< orphan*/  GOA_VCLK2 ; 
 int /*<<< orphan*/  GOA_VCLK_OPT1 ; 
 int GOA_VSTV1 ; 
 int /*<<< orphan*/  GOA_VSTV2 ; 
 int MCS_BT2CTR ; 
 int MCS_BT3CTR ; 
 int MCS_BT4CTR ; 
 int MCS_CMD1_UCS ; 
 int MCS_CMD2_P0 ; 
 int MCS_CMD2_P2 ; 
 int MCS_CMD2_P3 ; 
 int MCS_CMD_MODE_SW ; 
 int /*<<< orphan*/  MCS_EXT_PWR_IC ; 
 int /*<<< orphan*/  MCS_GAMMA_VN ; 
 int /*<<< orphan*/  MCS_GAMMA_VP ; 
 int /*<<< orphan*/  MCS_GOA_BS_SEL0 ; 
 int /*<<< orphan*/  MCS_GOA_BS_SEL1 ; 
 int /*<<< orphan*/  MCS_GOA_BS_SEL2 ; 
 int /*<<< orphan*/  MCS_GOA_BS_SEL3 ; 
 int /*<<< orphan*/  MCS_GOA_BS_SEL4 ; 
 int /*<<< orphan*/  MCS_GOA_CLK_GALLON ; 
 int /*<<< orphan*/  MCS_GOA_EQ ; 
 int /*<<< orphan*/  MCS_GOA_FS_SEL0 ; 
 int /*<<< orphan*/  MCS_GOA_FS_SEL1 ; 
 int /*<<< orphan*/  MCS_GOA_FS_SEL2 ; 
 int /*<<< orphan*/  MCS_GOA_FS_SEL3 ; 
 int /*<<< orphan*/  MCS_GOA_GPO1 ; 
 int /*<<< orphan*/  MCS_GOA_GPO2 ; 
 int MCS_INVCTR ; 
 int MCS_SDCTR ; 
 int MCS_SETAVDD ; 
 int MCS_SETAVEE ; 
 int /*<<< orphan*/  MCS_SETVGN ; 
 int /*<<< orphan*/  MCS_SETVGP ; 
 int MCS_SGOPCTR ; 
 int MCS_STBCTR ; 
 int MCS_SW_CTRL ; 
 int MCS_VCMCTR ; 
 int /*<<< orphan*/  dcs_write_cmd_seq (struct rm68200*,int,int,int,...) ; 
 int /*<<< orphan*/  dcs_write_seq (struct rm68200*,int,int,...) ; 

__attribute__((used)) static void rm68200_init_sequence(struct rm68200 *ctx)
{
	/* Enter CMD2 with page 0 */
	dcs_write_seq(ctx, MCS_CMD_MODE_SW, MCS_CMD2_P0);
	dcs_write_cmd_seq(ctx, MCS_EXT_PWR_IC, 0xC0, 0x53, 0x00);
	dcs_write_seq(ctx, MCS_BT2CTR, 0xE5);
	dcs_write_seq(ctx, MCS_SETAVDD, 0x0A);
	dcs_write_seq(ctx, MCS_SETAVEE, 0x0A);
	dcs_write_seq(ctx, MCS_SGOPCTR, 0x52);
	dcs_write_seq(ctx, MCS_BT3CTR, 0x53);
	dcs_write_seq(ctx, MCS_BT4CTR, 0x5A);
	dcs_write_seq(ctx, MCS_INVCTR, 0x00);
	dcs_write_seq(ctx, MCS_STBCTR, 0x0A);
	dcs_write_seq(ctx, MCS_SDCTR, 0x06);
	dcs_write_seq(ctx, MCS_VCMCTR, 0x56);
	dcs_write_seq(ctx, MCS_SETVGN, 0xA0, 0x00);
	dcs_write_seq(ctx, MCS_SETVGP, 0xA0, 0x00);
	dcs_write_seq(ctx, MCS_SW_CTRL, 0x11); /* 2 data lanes, see doc */

	dcs_write_seq(ctx, MCS_CMD_MODE_SW, MCS_CMD2_P2);
	dcs_write_seq(ctx, GOA_VSTV1, 0x05);
	dcs_write_seq(ctx, 0x02, 0x0B);
	dcs_write_seq(ctx, 0x03, 0x0F);
	dcs_write_seq(ctx, 0x04, 0x7D, 0x00, 0x50);
	dcs_write_cmd_seq(ctx, GOA_VSTV2, 0x05, 0x16, 0x0D, 0x11, 0x7D, 0x00,
			  0x50);
	dcs_write_cmd_seq(ctx, GOA_VCLK1, 0x07, 0x08, 0x01, 0x02, 0x00, 0x7D,
			  0x00, 0x85, 0x08);
	dcs_write_cmd_seq(ctx, GOA_VCLK2, 0x03, 0x04, 0x05, 0x06, 0x00, 0x7D,
			  0x00, 0x85, 0x08);
	dcs_write_seq(ctx, GOA_VCLK_OPT1, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		      0x00, 0x00, 0x00, 0x00);
	dcs_write_cmd_seq(ctx, GOA_BICLK1, 0x07, 0x08);
	dcs_write_seq(ctx, 0x2D, 0x01);
	dcs_write_seq(ctx, 0x2F, 0x02, 0x00, 0x40, 0x05, 0x08, 0x54, 0x7D,
		      0x00);
	dcs_write_cmd_seq(ctx, GOA_BICLK2, 0x03, 0x04, 0x05, 0x06, 0x00);
	dcs_write_seq(ctx, 0x3D, 0x40);
	dcs_write_seq(ctx, 0x3F, 0x05, 0x08, 0x54, 0x7D, 0x00);
	dcs_write_seq(ctx, GOA_BICLK3, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		      0x00, 0x00, 0x00, 0x00, 0x00);
	dcs_write_seq(ctx, GOA_BICLK4, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		      0x00, 0x00);
	dcs_write_seq(ctx, 0x58, 0x00, 0x00, 0x00);
	dcs_write_seq(ctx, GOA_BICLK_OPT1, 0x00, 0x00, 0x00, 0x00, 0x00);
	dcs_write_seq(ctx, GOA_BICLK_OPT2, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00);
	dcs_write_seq(ctx, MCS_GOA_GPO1, 0x00, 0x00, 0x00, 0x00);
	dcs_write_seq(ctx, MCS_GOA_GPO2, 0x00, 0x20, 0x00);
	dcs_write_seq(ctx, MCS_GOA_EQ, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08,
		      0x00, 0x00);
	dcs_write_seq(ctx, MCS_GOA_CLK_GALLON, 0x00, 0x00);
	dcs_write_cmd_seq(ctx, MCS_GOA_FS_SEL0, 0xBF, 0x02, 0x06, 0x14, 0x10,
			  0x16, 0x12, 0x08, 0x3F);
	dcs_write_cmd_seq(ctx, MCS_GOA_FS_SEL1, 0x3F, 0x3F, 0x3F, 0x3F, 0x0C,
			  0x0A, 0x0E, 0x3F, 0x3F, 0x00);
	dcs_write_cmd_seq(ctx, MCS_GOA_FS_SEL2, 0x04, 0x3F, 0x3F, 0x3F, 0x3F,
			  0x05, 0x01, 0x3F, 0x3F, 0x0F);
	dcs_write_cmd_seq(ctx, MCS_GOA_FS_SEL3, 0x0B, 0x0D, 0x3F, 0x3F, 0x3F,
			  0x3F);
	dcs_write_cmd_seq(ctx, 0xA2, 0x3F, 0x09, 0x13, 0x17, 0x11, 0x15);
	dcs_write_cmd_seq(ctx, 0xA9, 0x07, 0x03, 0x3F);
	dcs_write_cmd_seq(ctx, MCS_GOA_BS_SEL0, 0x3F, 0x05, 0x01, 0x17, 0x13,
			  0x15, 0x11, 0x0F, 0x3F);
	dcs_write_cmd_seq(ctx, MCS_GOA_BS_SEL1, 0x3F, 0x3F, 0x3F, 0x3F, 0x0B,
			  0x0D, 0x09, 0x3F, 0x3F, 0x07);
	dcs_write_cmd_seq(ctx, MCS_GOA_BS_SEL2, 0x03, 0x3F, 0x3F, 0x3F, 0x3F,
			  0x02, 0x06, 0x3F, 0x3F, 0x08);
	dcs_write_cmd_seq(ctx, MCS_GOA_BS_SEL3, 0x0C, 0x0A, 0x3F, 0x3F, 0x3F,
			  0x3F, 0x3F, 0x0E, 0x10, 0x14);
	dcs_write_cmd_seq(ctx, MCS_GOA_BS_SEL4, 0x12, 0x16, 0x00, 0x04, 0x3F);
	dcs_write_seq(ctx, 0xDC, 0x02);
	dcs_write_seq(ctx, 0xDE, 0x12);

	dcs_write_seq(ctx, MCS_CMD_MODE_SW, 0x0E); /* No documentation */
	dcs_write_seq(ctx, 0x01, 0x75);

	dcs_write_seq(ctx, MCS_CMD_MODE_SW, MCS_CMD2_P3);
	dcs_write_cmd_seq(ctx, MCS_GAMMA_VP, 0x00, 0x0C, 0x12, 0x0E, 0x06,
			  0x12, 0x0E, 0x0B, 0x15, 0x0B, 0x10, 0x07, 0x0F,
			  0x12, 0x0C, 0x00);
	dcs_write_cmd_seq(ctx, MCS_GAMMA_VN, 0x00, 0x0C, 0x12, 0x0E, 0x06,
			  0x12, 0x0E, 0x0B, 0x15, 0x0B, 0x10, 0x07, 0x0F,
			  0x12, 0x0C, 0x00);

	/* Exit CMD2 */
	dcs_write_seq(ctx, MCS_CMD_MODE_SW, MCS_CMD1_UCS);
}