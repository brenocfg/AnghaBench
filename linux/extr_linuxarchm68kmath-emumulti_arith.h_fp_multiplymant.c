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
union fp_mant64 {int /*<<< orphan*/ * m32; } ;
union fp_mant128 {int /*<<< orphan*/ * m32; } ;
struct TYPE_2__ {int /*<<< orphan*/ * m32; } ;
struct fp_ext {TYPE_1__ mant; } ;

/* Variables and functions */
 int /*<<< orphan*/  fp_addx96 (union fp_mant128*,union fp_mant64) ; 
 int /*<<< orphan*/  fp_mul64 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void fp_multiplymant(union fp_mant128 *dest, struct fp_ext *src1,
				   struct fp_ext *src2)
{
	union fp_mant64 temp;

	fp_mul64(dest->m32[0], dest->m32[1], src1->mant.m32[0], src2->mant.m32[0]);
	fp_mul64(dest->m32[2], dest->m32[3], src1->mant.m32[1], src2->mant.m32[1]);

	fp_mul64(temp.m32[0], temp.m32[1], src1->mant.m32[0], src2->mant.m32[1]);
	fp_addx96(dest, temp);

	fp_mul64(temp.m32[0], temp.m32[1], src1->mant.m32[1], src2->mant.m32[0]);
	fp_addx96(dest, temp);
}