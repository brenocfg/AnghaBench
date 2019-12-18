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
struct palmas_gpadc {int dummy; } ;

/* Variables and functions */
 int palmas_gpadc_enable (struct palmas_gpadc*,int,int) ; 
 int palmas_gpadc_start_mask_interrupt (struct palmas_gpadc*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int palmas_gpadc_read_prepare(struct palmas_gpadc *adc, int adc_chan)
{
	int ret;

	ret = palmas_gpadc_enable(adc, adc_chan, true);
	if (ret < 0)
		return ret;

	return palmas_gpadc_start_mask_interrupt(adc, 0);
}