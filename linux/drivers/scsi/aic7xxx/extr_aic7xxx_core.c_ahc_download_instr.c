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
struct ins_format1 {int opcode; int parity; size_t immediate; int source; int destination; int ret; } ;
struct ins_format3 {int address; int immediate; int source; int opcode; } ;
union ins_formats {int integer; int /*<<< orphan*/  bytes; struct ins_format1 format1; struct ins_format3 format3; } ;
typedef  size_t uint8_t ;
typedef  int uint32_t ;
typedef  int u_int ;
struct patch {int dummy; } ;
struct ahc_softc {int features; } ;

/* Variables and functions */
 int AHC_CMD_CHAN ; 
 int AHC_ULTRA2 ; 
#define  AIC_OP_ADC 142 
#define  AIC_OP_ADD 141 
#define  AIC_OP_AND 140 
#define  AIC_OP_BMOV 139 
#define  AIC_OP_CALL 138 
#define  AIC_OP_JC 137 
#define  AIC_OP_JE 136 
#define  AIC_OP_JMP 135 
#define  AIC_OP_JNC 134 
#define  AIC_OP_JNE 133 
#define  AIC_OP_JNZ 132 
#define  AIC_OP_JZ 131 
#define  AIC_OP_OR 130 
#define  AIC_OP_ROL 129 
#define  AIC_OP_XOR 128 
 int /*<<< orphan*/  SEQRAM ; 
 int /*<<< orphan*/  ahc_check_patch (struct ahc_softc*,struct patch const**,int,int*) ; 
 int ahc_htole32 (int) ; 
 int ahc_le32toh (int) ; 
 int /*<<< orphan*/  ahc_name (struct ahc_softc*) ; 
 int /*<<< orphan*/  ahc_outsb (struct ahc_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int min (int,int) ; 
 int /*<<< orphan*/  panic (char*,...) ; 
 struct patch* patches ; 
 int /*<<< orphan*/ * seqprog ; 

__attribute__((used)) static void
ahc_download_instr(struct ahc_softc *ahc, u_int instrptr, uint8_t *dconsts)
{
	union	ins_formats instr;
	struct	ins_format1 *fmt1_ins;
	struct	ins_format3 *fmt3_ins;
	u_int	opcode;

	/*
	 * The firmware is always compiled into a little endian format.
	 */
	instr.integer = ahc_le32toh(*(uint32_t*)&seqprog[instrptr * 4]);

	fmt1_ins = &instr.format1;
	fmt3_ins = NULL;

	/* Pull the opcode */
	opcode = instr.format1.opcode;
	switch (opcode) {
	case AIC_OP_JMP:
	case AIC_OP_JC:
	case AIC_OP_JNC:
	case AIC_OP_CALL:
	case AIC_OP_JNE:
	case AIC_OP_JNZ:
	case AIC_OP_JE:
	case AIC_OP_JZ:
	{
		const struct patch *cur_patch;
		int address_offset;
		u_int address;
		u_int skip_addr;
		u_int i;

		fmt3_ins = &instr.format3;
		address_offset = 0;
		address = fmt3_ins->address;
		cur_patch = patches;
		skip_addr = 0;

		for (i = 0; i < address;) {

			ahc_check_patch(ahc, &cur_patch, i, &skip_addr);

			if (skip_addr > i) {
				int end_addr;

				end_addr = min(address, skip_addr);
				address_offset += end_addr - i;
				i = skip_addr;
			} else {
				i++;
			}
		}
		address -= address_offset;
		fmt3_ins->address = address;
	}
		/* fall through */
	case AIC_OP_OR:
	case AIC_OP_AND:
	case AIC_OP_XOR:
	case AIC_OP_ADD:
	case AIC_OP_ADC:
	case AIC_OP_BMOV:
		if (fmt1_ins->parity != 0) {
			fmt1_ins->immediate = dconsts[fmt1_ins->immediate];
		}
		fmt1_ins->parity = 0;
		if ((ahc->features & AHC_CMD_CHAN) == 0
		 && opcode == AIC_OP_BMOV) {
			/*
			 * Block move was added at the same time
			 * as the command channel.  Verify that
			 * this is only a move of a single element
			 * and convert the BMOV to a MOV
			 * (AND with an immediate of FF).
			 */
			if (fmt1_ins->immediate != 1)
				panic("%s: BMOV not supported\n",
				      ahc_name(ahc));
			fmt1_ins->opcode = AIC_OP_AND;
			fmt1_ins->immediate = 0xff;
		}
		/* fall through */
	case AIC_OP_ROL:
		if ((ahc->features & AHC_ULTRA2) != 0) {
			int i, count;

			/* Calculate odd parity for the instruction */
			for (i = 0, count = 0; i < 31; i++) {
				uint32_t mask;

				mask = 0x01 << i;
				if ((instr.integer & mask) != 0)
					count++;
			}
			if ((count & 0x01) == 0)
				instr.format1.parity = 1;
		} else {
			/* Compress the instruction for older sequencers */
			if (fmt3_ins != NULL) {
				instr.integer =
					fmt3_ins->immediate
				      | (fmt3_ins->source << 8)
				      | (fmt3_ins->address << 16)
				      |	(fmt3_ins->opcode << 25);
			} else {
				instr.integer =
					fmt1_ins->immediate
				      | (fmt1_ins->source << 8)
				      | (fmt1_ins->destination << 16)
				      |	(fmt1_ins->ret << 24)
				      |	(fmt1_ins->opcode << 25);
			}
		}
		/* The sequencer is a little endian cpu */
		instr.integer = ahc_htole32(instr.integer);
		ahc_outsb(ahc, SEQRAM, instr.bytes, 4);
		break;
	default:
		panic("Unknown opcode encountered in seq program");
		break;
	}
}