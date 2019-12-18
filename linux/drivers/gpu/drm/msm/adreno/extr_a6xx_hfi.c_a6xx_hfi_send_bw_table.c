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
struct a6xx_hfi_msg_bw_table {int bw_level_num; int ddr_cmds_num; int ddr_wait_bitmask; int* ddr_cmds_addrs; int** ddr_cmds_data; int cnoc_cmds_num; int cnoc_wait_bitmask; int* cnoc_cmds_addrs; int** cnoc_cmds_data; int /*<<< orphan*/  member_0; } ;
struct a6xx_gmu {int dummy; } ;
typedef  int /*<<< orphan*/  msg ;

/* Variables and functions */
 int /*<<< orphan*/  HFI_H2F_MSG_BW_TABLE ; 
 int a6xx_hfi_send_msg (struct a6xx_gmu*,int /*<<< orphan*/ ,struct a6xx_hfi_msg_bw_table*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int a6xx_hfi_send_bw_table(struct a6xx_gmu *gmu)
{
	struct a6xx_hfi_msg_bw_table msg = { 0 };

	/*
	 * The sdm845 GMU doesn't do bus frequency scaling on its own but it
	 * does need at least one entry in the list because it might be accessed
	 * when the GMU is shutting down. Send a single "off" entry.
	 */

	msg.bw_level_num = 1;

	msg.ddr_cmds_num = 3;
	msg.ddr_wait_bitmask = 0x07;

	msg.ddr_cmds_addrs[0] = 0x50000;
	msg.ddr_cmds_addrs[1] = 0x5005c;
	msg.ddr_cmds_addrs[2] = 0x5000c;

	msg.ddr_cmds_data[0][0] =  0x40000000;
	msg.ddr_cmds_data[0][1] =  0x40000000;
	msg.ddr_cmds_data[0][2] =  0x40000000;

	/*
	 * These are the CX (CNOC) votes.  This is used but the values for the
	 * sdm845 GMU are known and fixed so we can hard code them.
	 */

	msg.cnoc_cmds_num = 3;
	msg.cnoc_wait_bitmask = 0x05;

	msg.cnoc_cmds_addrs[0] = 0x50034;
	msg.cnoc_cmds_addrs[1] = 0x5007c;
	msg.cnoc_cmds_addrs[2] = 0x5004c;

	msg.cnoc_cmds_data[0][0] =  0x40000000;
	msg.cnoc_cmds_data[0][1] =  0x00000000;
	msg.cnoc_cmds_data[0][2] =  0x40000000;

	msg.cnoc_cmds_data[1][0] =  0x60000001;
	msg.cnoc_cmds_data[1][1] =  0x20000001;
	msg.cnoc_cmds_data[1][2] =  0x60000001;

	return a6xx_hfi_send_msg(gmu, HFI_H2F_MSG_BW_TABLE, &msg, sizeof(msg),
		NULL, 0);
}