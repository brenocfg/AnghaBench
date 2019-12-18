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
struct stm32_dfsdm_filter_osr {int max; int lshift; } ;
struct stm32_dfsdm_filter {size_t fast; struct stm32_dfsdm_filter_osr* flo; } ;
struct stm32_dfsdm_adc {size_t fl_id; unsigned int nconv; TYPE_1__* dfsdm; } ;
typedef  int s32 ;
struct TYPE_2__ {struct stm32_dfsdm_filter* fl_list; } ;

/* Variables and functions */

__attribute__((used)) static inline void stm32_dfsdm_process_data(struct stm32_dfsdm_adc *adc,
					    s32 *buffer)
{
	struct stm32_dfsdm_filter *fl = &adc->dfsdm->fl_list[adc->fl_id];
	struct stm32_dfsdm_filter_osr *flo = &fl->flo[fl->fast];
	unsigned int i = adc->nconv;
	s32 *ptr = buffer;

	while (i--) {
		/* Mask 8 LSB that contains the channel ID */
		*ptr &= 0xFFFFFF00;
		/* Convert 2^(n-1) sample to 2^(n-1)-1 to avoid wrap-around */
		if (*ptr > flo->max)
			*ptr -= 1;
		/*
		 * Samples from filter are retrieved with 23 bits resolution
		 * or less. Shift left to align MSB on 24 bits.
		 */
		*ptr <<= flo->lshift;

		ptr++;
	}
}