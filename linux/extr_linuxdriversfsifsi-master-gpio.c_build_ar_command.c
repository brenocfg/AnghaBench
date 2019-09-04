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
typedef  int uint8_t ;
typedef  int uint32_t ;
struct fsi_master_gpio {int dummy; } ;
struct fsi_gpio_msg {scalar_t__ msg; scalar_t__ bits; } ;

/* Variables and functions */
 int FSI_CMD_ABS_AR ; 
 int FSI_CMD_REL_AR ; 
 int FSI_CMD_SAME_AR ; 
 scalar_t__ check_relative_address (struct fsi_master_gpio*,int,int,int*) ; 
 scalar_t__ check_same_address (struct fsi_master_gpio*,int,int) ; 
 int /*<<< orphan*/  msg_push_bits (struct fsi_gpio_msg*,int,int) ; 
 int /*<<< orphan*/  msg_push_crc (struct fsi_gpio_msg*) ; 
 int /*<<< orphan*/  trace_fsi_master_gpio_cmd_abs_addr (struct fsi_master_gpio*,int) ; 
 int /*<<< orphan*/  trace_fsi_master_gpio_cmd_rel_addr (struct fsi_master_gpio*,int) ; 
 int /*<<< orphan*/  trace_fsi_master_gpio_cmd_same_addr (struct fsi_master_gpio*) ; 

__attribute__((used)) static void build_ar_command(struct fsi_master_gpio *master,
		struct fsi_gpio_msg *cmd, uint8_t id,
		uint32_t addr, size_t size, const void *data)
{
	int i, addr_bits, opcode_bits;
	bool write = !!data;
	uint8_t ds, opcode;
	uint32_t rel_addr;

	cmd->bits = 0;
	cmd->msg = 0;

	/* we have 21 bits of address max */
	addr &= ((1 << 21) - 1);

	/* cmd opcodes are variable length - SAME_AR is only two bits */
	opcode_bits = 3;

	if (check_same_address(master, id, addr)) {
		/* we still address the byte offset within the word */
		addr_bits = 2;
		opcode_bits = 2;
		opcode = FSI_CMD_SAME_AR;
		trace_fsi_master_gpio_cmd_same_addr(master);

	} else if (check_relative_address(master, id, addr, &rel_addr)) {
		/* 8 bits plus sign */
		addr_bits = 9;
		addr = rel_addr;
		opcode = FSI_CMD_REL_AR;
		trace_fsi_master_gpio_cmd_rel_addr(master, rel_addr);

	} else {
		addr_bits = 21;
		opcode = FSI_CMD_ABS_AR;
		trace_fsi_master_gpio_cmd_abs_addr(master, addr);
	}

	/*
	 * The read/write size is encoded in the lower bits of the address
	 * (as it must be naturally-aligned), and the following ds bit.
	 *
	 *	size	addr:1	addr:0	ds
	 *	1	x	x	0
	 *	2	x	0	1
	 *	4	0	1	1
	 *
	 */
	ds = size > 1 ? 1 : 0;
	addr &= ~(size - 1);
	if (size == 4)
		addr |= 1;

	msg_push_bits(cmd, id, 2);
	msg_push_bits(cmd, opcode, opcode_bits);
	msg_push_bits(cmd, write ? 0 : 1, 1);
	msg_push_bits(cmd, addr, addr_bits);
	msg_push_bits(cmd, ds, 1);
	for (i = 0; write && i < size; i++)
		msg_push_bits(cmd, ((uint8_t *)data)[i], 8);

	msg_push_crc(cmd);
}