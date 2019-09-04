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
typedef  int uint32_t ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int,int,int,int,int,int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 TYPE_1__ ipu_data ; 

__attribute__((used)) static int calc_resize_coeffs(uint32_t in_size, uint32_t out_size,
			      uint32_t *resize_coeff,
			      uint32_t *downsize_coeff)
{
	uint32_t temp_size;
	uint32_t temp_downsize;

	*resize_coeff	= 1 << 13;
	*downsize_coeff	= 1 << 13;

	/* Cannot downsize more than 8:1 */
	if (out_size << 3 < in_size)
		return -EINVAL;

	/* compute downsizing coefficient */
	temp_downsize = 0;
	temp_size = in_size;
	while (temp_size >= out_size * 2 && temp_downsize < 2) {
		temp_size >>= 1;
		temp_downsize++;
	}
	*downsize_coeff = temp_downsize;

	/*
	 * compute resizing coefficient using the following formula:
	 * resize_coeff = M*(SI -1)/(SO - 1)
	 * where M = 2^13, SI - input size, SO - output size
	 */
	*resize_coeff = (8192L * (temp_size - 1)) / (out_size - 1);
	if (*resize_coeff >= 16384L) {
		dev_err(ipu_data.dev, "Warning! Overflow on resize coeff.\n");
		*resize_coeff = 0x3FFF;
	}

	dev_dbg(ipu_data.dev, "resizing from %u -> %u pixels, "
		"downsize=%u, resize=%u.%lu (reg=%u)\n", in_size, out_size,
		*downsize_coeff, *resize_coeff >= 8192L ? 1 : 0,
		((*resize_coeff & 0x1FFF) * 10000L) / 8192L, *resize_coeff);

	return 0;
}