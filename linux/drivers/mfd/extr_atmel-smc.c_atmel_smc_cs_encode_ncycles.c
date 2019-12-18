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

/* Variables and functions */
 int ERANGE ; 
 unsigned int GENMASK (unsigned int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int atmel_smc_cs_encode_ncycles(unsigned int ncycles,
				       unsigned int msbpos,
				       unsigned int msbwidth,
				       unsigned int msbfactor,
				       unsigned int *encodedval)
{
	unsigned int lsbmask = GENMASK(msbpos - 1, 0);
	unsigned int msbmask = GENMASK(msbwidth - 1, 0);
	unsigned int msb, lsb;
	int ret = 0;

	msb = ncycles / msbfactor;
	lsb = ncycles % msbfactor;

	if (lsb > lsbmask) {
		lsb = 0;
		msb++;
	}

	/*
	 * Let's just put the maximum we can if the requested setting does
	 * not fit in the register field.
	 * We still return -ERANGE in case the caller cares.
	 */
	if (msb > msbmask) {
		msb = msbmask;
		lsb = lsbmask;
		ret = -ERANGE;
	}

	*encodedval = (msb << msbpos) | lsb;

	return ret;
}