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
typedef  scalar_t__ u8 ;

/* Variables and functions */
 scalar_t__ nand_id_has_period (scalar_t__*,int,int) ; 

__attribute__((used)) static int nand_id_len(u8 *id_data, int arrlen)
{
	int last_nonzero, period;

	/* Find last non-zero byte */
	for (last_nonzero = arrlen - 1; last_nonzero >= 0; last_nonzero--)
		if (id_data[last_nonzero])
			break;

	/* All zeros */
	if (last_nonzero < 0)
		return 0;

	/* Calculate wraparound period */
	for (period = 1; period < arrlen; period++)
		if (nand_id_has_period(id_data, arrlen, period))
			break;

	/* There's a repeated pattern */
	if (period < arrlen)
		return period;

	/* There are trailing zeros */
	if (last_nonzero < arrlen - 1)
		return last_nonzero + 1;

	/* No pattern detected */
	return arrlen;
}