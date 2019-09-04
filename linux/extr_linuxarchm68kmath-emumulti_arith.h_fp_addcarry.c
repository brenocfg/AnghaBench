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
struct TYPE_2__ {int* m32; scalar_t__ m64; } ;
struct fp_ext {int exp; int lowmant; TYPE_1__ mant; } ;

/* Variables and functions */
 int /*<<< orphan*/  FPSR_EXC_INEX2 ; 
 int /*<<< orphan*/  FPSR_EXC_OVFL ; 
 int /*<<< orphan*/  fp_set_sr (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int fp_addcarry(struct fp_ext *reg)
{
	if (++reg->exp == 0x7fff) {
		if (reg->mant.m64)
			fp_set_sr(FPSR_EXC_INEX2);
		reg->mant.m64 = 0;
		fp_set_sr(FPSR_EXC_OVFL);
		return 0;
	}
	reg->lowmant = (reg->mant.m32[1] << 7) | (reg->lowmant ? 1 : 0);
	reg->mant.m32[1] = (reg->mant.m32[1] >> 1) |
			   (reg->mant.m32[0] << 31);
	reg->mant.m32[0] = (reg->mant.m32[0] >> 1) | 0x80000000;

	return 1;
}