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
struct ni_gpct_device {scalar_t__ variant; } ;
struct ni_gpct {unsigned int counter_index; struct ni_gpct_device* counter_dev; } ;

/* Variables and functions */
 int EINVAL ; 
 unsigned int NITIO_ABZ_REG (unsigned int) ; 
 unsigned int NI_CtrA (int) ; 
 unsigned int NI_CtrB (int) ; 
 unsigned int NI_CtrZ (int) ; 
 unsigned int NI_GPCT_SOURCE_ENCODER_A ; 
 unsigned int NI_GPCT_SOURCE_ENCODER_B ; 
 unsigned int NI_GPCT_SOURCE_ENCODER_Z ; 
 scalar_t__ ni_gpct_variant_m_series ; 
 unsigned int ni_tio_get_soft_copy (struct ni_gpct*,unsigned int) ; 

__attribute__((used)) static int ni_tio_get_other_src(struct ni_gpct *counter, unsigned int index,
				unsigned int *source)
{
	struct ni_gpct_device *counter_dev = counter->counter_dev;
	unsigned int cidx = counter->counter_index;
	unsigned int abz_reg, shift, mask;

	if (counter_dev->variant != ni_gpct_variant_m_series)
		/* A,B,Z only valid for m-series */
		return -EINVAL;

	abz_reg = NITIO_ABZ_REG(cidx);

	/* allow for new device-global names */
	if (index == NI_GPCT_SOURCE_ENCODER_A ||
	    (index >= NI_CtrA(0) && index <= NI_CtrA(-1))) {
		shift = 10;
	} else if (index == NI_GPCT_SOURCE_ENCODER_B ||
	    (index >= NI_CtrB(0) && index <= NI_CtrB(-1))) {
		shift = 5;
	} else if (index == NI_GPCT_SOURCE_ENCODER_Z ||
	    (index >= NI_CtrZ(0) && index <= NI_CtrZ(-1))) {
		shift = 0;
	} else {
		return -EINVAL;
	}

	mask = 0x1f;

	*source = (ni_tio_get_soft_copy(counter, abz_reg) >> shift) & mask;
	return 0;
}