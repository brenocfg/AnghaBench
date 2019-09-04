#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u32 ;
struct TYPE_3__ {int /*<<< orphan*/  offset; int /*<<< orphan*/  len; } ;
struct bnx2_rv2p_fw_file_entry {int /*<<< orphan*/ * fixup; TYPE_1__ rv2p; } ;
struct bnx2 {TYPE_2__* rv2p_firmware; } ;
typedef  int /*<<< orphan*/  __be32 ;
struct TYPE_4__ {scalar_t__ data; } ;

/* Variables and functions */
 scalar_t__ BNX2_RV2P_COMMAND ; 
 scalar_t__ BNX2_RV2P_COMMAND_PROC1_RESET ; 
 scalar_t__ BNX2_RV2P_COMMAND_PROC2_RESET ; 
 scalar_t__ BNX2_RV2P_INSTR_HIGH ; 
 scalar_t__ BNX2_RV2P_INSTR_LOW ; 
 scalar_t__ BNX2_RV2P_PROC1_ADDR_CMD ; 
 scalar_t__ BNX2_RV2P_PROC1_ADDR_CMD_RDWR ; 
 scalar_t__ BNX2_RV2P_PROC2_ADDR_CMD ; 
 scalar_t__ BNX2_RV2P_PROC2_ADDR_CMD_RDWR ; 
 int /*<<< orphan*/  BNX2_WR (struct bnx2*,scalar_t__,scalar_t__) ; 
 scalar_t__ RV2P_PROC1 ; 
 scalar_t__ be32_to_cpu (int /*<<< orphan*/ ) ; 
 scalar_t__ rv2p_fw_fixup (scalar_t__,int,scalar_t__,scalar_t__) ; 

__attribute__((used)) static int
load_rv2p_fw(struct bnx2 *bp, u32 rv2p_proc,
	     const struct bnx2_rv2p_fw_file_entry *fw_entry)
{
	u32 rv2p_code_len, file_offset;
	__be32 *rv2p_code;
	int i;
	u32 val, cmd, addr;

	rv2p_code_len = be32_to_cpu(fw_entry->rv2p.len);
	file_offset = be32_to_cpu(fw_entry->rv2p.offset);

	rv2p_code = (__be32 *)(bp->rv2p_firmware->data + file_offset);

	if (rv2p_proc == RV2P_PROC1) {
		cmd = BNX2_RV2P_PROC1_ADDR_CMD_RDWR;
		addr = BNX2_RV2P_PROC1_ADDR_CMD;
	} else {
		cmd = BNX2_RV2P_PROC2_ADDR_CMD_RDWR;
		addr = BNX2_RV2P_PROC2_ADDR_CMD;
	}

	for (i = 0; i < rv2p_code_len; i += 8) {
		BNX2_WR(bp, BNX2_RV2P_INSTR_HIGH, be32_to_cpu(*rv2p_code));
		rv2p_code++;
		BNX2_WR(bp, BNX2_RV2P_INSTR_LOW, be32_to_cpu(*rv2p_code));
		rv2p_code++;

		val = (i / 8) | cmd;
		BNX2_WR(bp, addr, val);
	}

	rv2p_code = (__be32 *)(bp->rv2p_firmware->data + file_offset);
	for (i = 0; i < 8; i++) {
		u32 loc, code;

		loc = be32_to_cpu(fw_entry->fixup[i]);
		if (loc && ((loc * 4) < rv2p_code_len)) {
			code = be32_to_cpu(*(rv2p_code + loc - 1));
			BNX2_WR(bp, BNX2_RV2P_INSTR_HIGH, code);
			code = be32_to_cpu(*(rv2p_code + loc));
			code = rv2p_fw_fixup(rv2p_proc, i, loc, code);
			BNX2_WR(bp, BNX2_RV2P_INSTR_LOW, code);

			val = (loc / 2) | cmd;
			BNX2_WR(bp, addr, val);
		}
	}

	/* Reset the processor, un-stall is done later. */
	if (rv2p_proc == RV2P_PROC1) {
		BNX2_WR(bp, BNX2_RV2P_COMMAND, BNX2_RV2P_COMMAND_PROC1_RESET);
	}
	else {
		BNX2_WR(bp, BNX2_RV2P_COMMAND, BNX2_RV2P_COMMAND_PROC2_RESET);
	}

	return 0;
}