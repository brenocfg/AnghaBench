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
struct pt_regs {int dummy; } ;
struct fpustate {int dummy; } ;
typedef  int s16 ;

/* Variables and functions */
 struct fpustate* FPUSTATE ; 
 int /*<<< orphan*/  RD (unsigned int) ; 
 int /*<<< orphan*/  RS1 (unsigned int) ; 
 int /*<<< orphan*/  RS2 (unsigned int) ; 
 unsigned long* fpd_regaddr (struct fpustate*,int /*<<< orphan*/ ) ; 
 unsigned long fpd_regval (struct fpustate*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void pdist(struct pt_regs *regs, unsigned int insn)
{
	struct fpustate *f = FPUSTATE;
	unsigned long rs1, rs2, *rd, rd_val;
	unsigned long i;

	rs1 = fpd_regval(f, RS1(insn));
	rs2 = fpd_regval(f, RS2(insn));
	rd = fpd_regaddr(f, RD(insn));

	rd_val = *rd;

	for (i = 0; i < 8; i++) {
		s16 s1, s2;

		s1 = (rs1 >> (56 - (i * 8))) & 0xff;
		s2 = (rs2 >> (56 - (i * 8))) & 0xff;

		/* Absolute value of difference. */
		s1 -= s2;
		if (s1 < 0)
			s1 = ~s1 + 1;

		rd_val += s1;
	}

	*rd = rd_val;
}