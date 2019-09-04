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
struct stm_fs {unsigned long ndiv; } ;

/* Variables and functions */
 int EINVAL ; 

__attribute__((used)) static int clk_fs660c32_vco_get_params(unsigned long input,
				unsigned long output, struct stm_fs *fs)
{
/* Formula
   VCO frequency = (fin x ndiv) / pdiv
   ndiv = VCOfreq * pdiv / fin
   */
	unsigned long pdiv = 1, n;

	/* Output clock range: 384Mhz to 660Mhz */
	if (output < 384000000 || output > 660000000)
		return -EINVAL;

	if (input > 40000000)
		/* This means that PDIV would be 2 instead of 1.
		   Not supported today. */
		return -EINVAL;

	input /= 1000;
	output /= 1000;

	n = output * pdiv / input;
	if (n < 16)
		n = 16;
	fs->ndiv = n - 16; /* Converting formula value to reg value */

	return 0;
}