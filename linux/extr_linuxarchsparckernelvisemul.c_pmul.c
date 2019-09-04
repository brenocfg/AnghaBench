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
typedef  int u16 ;
struct pt_regs {int dummy; } ;
struct fpustate {int dummy; } ;
typedef  int s16 ;

/* Variables and functions */
#define  FMUL8SUx16_OPF 134 
#define  FMUL8ULx16_OPF 133 
#define  FMUL8x16AL_OPF 132 
#define  FMUL8x16AU_OPF 131 
#define  FMUL8x16_OPF 130 
#define  FMULD8SUx16_OPF 129 
#define  FMULD8ULx16_OPF 128 
 struct fpustate* FPUSTATE ; 
 int /*<<< orphan*/  RD (unsigned int) ; 
 int /*<<< orphan*/  RS1 (unsigned int) ; 
 int /*<<< orphan*/  RS2 (unsigned int) ; 
 unsigned long* fpd_regaddr (struct fpustate*,int /*<<< orphan*/ ) ; 
 unsigned long fpd_regval (struct fpustate*,int /*<<< orphan*/ ) ; 
 unsigned long fps_regval (struct fpustate*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void pmul(struct pt_regs *regs, unsigned int insn, unsigned int opf)
{
	struct fpustate *f = FPUSTATE;
	unsigned long rs1, rs2, rd_val;

	switch (opf) {
	case FMUL8x16_OPF: {
		unsigned long byte;

		rs1 = fps_regval(f, RS1(insn));
		rs2 = fpd_regval(f, RS2(insn));

		rd_val = 0;
		for (byte = 0; byte < 4; byte++) {
			u16 src1 = (rs1 >> (byte *  8)) & 0x00ff;
			s16 src2 = (rs2 >> (byte * 16)) & 0xffff;
			u32 prod = src1 * src2;
			u16 scaled = ((prod & 0x00ffff00) >> 8);

			/* Round up.  */
			if (prod & 0x80)
				scaled++;
			rd_val |= ((scaled & 0xffffUL) << (byte * 16UL));
		}

		*fpd_regaddr(f, RD(insn)) = rd_val;
		break;
	}

	case FMUL8x16AU_OPF:
	case FMUL8x16AL_OPF: {
		unsigned long byte;
		s16 src2;

		rs1 = fps_regval(f, RS1(insn));
		rs2 = fps_regval(f, RS2(insn));

		rd_val = 0;
		src2 = rs2 >> (opf == FMUL8x16AU_OPF ? 16 : 0);
		for (byte = 0; byte < 4; byte++) {
			u16 src1 = (rs1 >> (byte * 8)) & 0x00ff;
			u32 prod = src1 * src2;
			u16 scaled = ((prod & 0x00ffff00) >> 8);

			/* Round up.  */
			if (prod & 0x80)
				scaled++;
			rd_val |= ((scaled & 0xffffUL) << (byte * 16UL));
		}

		*fpd_regaddr(f, RD(insn)) = rd_val;
		break;
	}

	case FMUL8SUx16_OPF:
	case FMUL8ULx16_OPF: {
		unsigned long byte, ushift;

		rs1 = fpd_regval(f, RS1(insn));
		rs2 = fpd_regval(f, RS2(insn));

		rd_val = 0;
		ushift = (opf == FMUL8SUx16_OPF) ? 8 : 0;
		for (byte = 0; byte < 4; byte++) {
			u16 src1;
			s16 src2;
			u32 prod;
			u16 scaled;

			src1 = ((rs1 >> ((16 * byte) + ushift)) & 0x00ff);
			src2 = ((rs2 >> (16 * byte)) & 0xffff);
			prod = src1 * src2;
			scaled = ((prod & 0x00ffff00) >> 8);

			/* Round up.  */
			if (prod & 0x80)
				scaled++;
			rd_val |= ((scaled & 0xffffUL) << (byte * 16UL));
		}

		*fpd_regaddr(f, RD(insn)) = rd_val;
		break;
	}

	case FMULD8SUx16_OPF:
	case FMULD8ULx16_OPF: {
		unsigned long byte, ushift;

		rs1 = fps_regval(f, RS1(insn));
		rs2 = fps_regval(f, RS2(insn));

		rd_val = 0;
		ushift = (opf == FMULD8SUx16_OPF) ? 8 : 0;
		for (byte = 0; byte < 2; byte++) {
			u16 src1;
			s16 src2;
			u32 prod;
			u16 scaled;

			src1 = ((rs1 >> ((16 * byte) + ushift)) & 0x00ff);
			src2 = ((rs2 >> (16 * byte)) & 0xffff);
			prod = src1 * src2;
			scaled = ((prod & 0x00ffff00) >> 8);

			/* Round up.  */
			if (prod & 0x80)
				scaled++;
			rd_val |= ((scaled & 0xffffUL) <<
				   ((byte * 32UL) + 7UL));
		}
		*fpd_regaddr(f, RD(insn)) = rd_val;
		break;
	}
	}
}