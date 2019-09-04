#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct pt_regs {int dummy; } ;
struct fpustate {int dummy; } ;
typedef  int s64 ;
typedef  unsigned long s32 ;
typedef  unsigned long s16 ;
struct TYPE_2__ {unsigned long* gsr; } ;

/* Variables and functions */
#define  FEXPAND_OPF 132 
#define  FPACK16_OPF 131 
#define  FPACK32_OPF 130 
#define  FPACKFIX_OPF 129 
#define  FPMERGE_OPF 128 
 struct fpustate* FPUSTATE ; 
 int /*<<< orphan*/  RD (unsigned int) ; 
 int /*<<< orphan*/  RS1 (unsigned int) ; 
 int /*<<< orphan*/  RS2 (unsigned int) ; 
 TYPE_1__* current_thread_info () ; 
 unsigned long* fpd_regaddr (struct fpustate*,int /*<<< orphan*/ ) ; 
 unsigned long fpd_regval (struct fpustate*,int /*<<< orphan*/ ) ; 
 unsigned long* fps_regaddr (struct fpustate*,int /*<<< orphan*/ ) ; 
 unsigned long fps_regval (struct fpustate*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void pformat(struct pt_regs *regs, unsigned int insn, unsigned int opf)
{
	struct fpustate *f = FPUSTATE;
	unsigned long rs1, rs2, gsr, scale, rd_val;

	gsr = current_thread_info()->gsr[0];
	scale = (gsr >> 3) & (opf == FPACK16_OPF ? 0xf : 0x1f);
	switch (opf) {
	case FPACK16_OPF: {
		unsigned long byte;

		rs2 = fpd_regval(f, RS2(insn));
		rd_val = 0;
		for (byte = 0; byte < 4; byte++) {
			unsigned int val;
			s16 src = (rs2 >> (byte * 16UL)) & 0xffffUL;
			int scaled = src << scale;
			int from_fixed = scaled >> 7;

			val = ((from_fixed < 0) ?
			       0 :
			       (from_fixed > 255) ?
			       255 : from_fixed);

			rd_val |= (val << (8 * byte));
		}
		*fps_regaddr(f, RD(insn)) = rd_val;
		break;
	}

	case FPACK32_OPF: {
		unsigned long word;

		rs1 = fpd_regval(f, RS1(insn));
		rs2 = fpd_regval(f, RS2(insn));
		rd_val = (rs1 << 8) & ~(0x000000ff000000ffUL);
		for (word = 0; word < 2; word++) {
			unsigned long val;
			s32 src = (rs2 >> (word * 32UL));
			s64 scaled = src << scale;
			s64 from_fixed = scaled >> 23;

			val = ((from_fixed < 0) ?
			       0 :
			       (from_fixed > 255) ?
			       255 : from_fixed);

			rd_val |= (val << (32 * word));
		}
		*fpd_regaddr(f, RD(insn)) = rd_val;
		break;
	}

	case FPACKFIX_OPF: {
		unsigned long word;

		rs2 = fpd_regval(f, RS2(insn));

		rd_val = 0;
		for (word = 0; word < 2; word++) {
			long val;
			s32 src = (rs2 >> (word * 32UL));
			s64 scaled = src << scale;
			s64 from_fixed = scaled >> 16;

			val = ((from_fixed < -32768) ?
			       -32768 :
			       (from_fixed > 32767) ?
			       32767 : from_fixed);

			rd_val |= ((val & 0xffff) << (word * 16));
		}
		*fps_regaddr(f, RD(insn)) = rd_val;
		break;
	}

	case FEXPAND_OPF: {
		unsigned long byte;

		rs2 = fps_regval(f, RS2(insn));

		rd_val = 0;
		for (byte = 0; byte < 4; byte++) {
			unsigned long val;
			u8 src = (rs2 >> (byte * 8)) & 0xff;

			val = src << 4;

			rd_val |= (val << (byte * 16));
		}
		*fpd_regaddr(f, RD(insn)) = rd_val;
		break;
	}

	case FPMERGE_OPF: {
		rs1 = fps_regval(f, RS1(insn));
		rs2 = fps_regval(f, RS2(insn));

		rd_val = (((rs2 & 0x000000ff) <<  0) |
			  ((rs1 & 0x000000ff) <<  8) |
			  ((rs2 & 0x0000ff00) <<  8) |
			  ((rs1 & 0x0000ff00) << 16) |
			  ((rs2 & 0x00ff0000) << 16) |
			  ((rs1 & 0x00ff0000) << 24) |
			  ((rs2 & 0xff000000) << 24) |
			  ((rs1 & 0xff000000) << 32));
		*fpd_regaddr(f, RD(insn)) = rd_val;
		break;
	}
	}
}