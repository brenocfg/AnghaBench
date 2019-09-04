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
typedef  unsigned long u64 ;
typedef  long u32 ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  do_div (unsigned long,unsigned long) ; 

__attribute__((used)) static int __clk_pllv2_set_rate(unsigned long rate, unsigned long parent_rate,
		u32 *dp_op, u32 *dp_mfd, u32 *dp_mfn)
{
	u32 reg;
	long mfi, pdf, mfn, mfd = 999999;
	u64 temp64;
	unsigned long quad_parent_rate;

	quad_parent_rate = 4 * parent_rate;
	pdf = mfi = -1;
	while (++pdf < 16 && mfi < 5)
		mfi = rate * (pdf+1) / quad_parent_rate;
	if (mfi > 15)
		return -EINVAL;
	pdf--;

	temp64 = rate * (pdf + 1) - quad_parent_rate * mfi;
	do_div(temp64, quad_parent_rate / 1000000);
	mfn = (long)temp64;

	reg = mfi << 4 | pdf;

	*dp_op = reg;
	*dp_mfd = mfd;
	*dp_mfn = mfn;

	return 0;
}