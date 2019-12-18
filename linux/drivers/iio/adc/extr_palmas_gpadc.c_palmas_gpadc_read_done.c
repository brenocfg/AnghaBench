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
 int /*<<< orphan*/  palmas_gpadc_enable (struct palmas_gpadc*,int,int) ; 
 int /*<<< orphan*/  palmas_gpadc_start_mask_interrupt (struct palmas_gpadc*,int) ; 

__attribute__((used)) static void palmas_gpadc_read_done(struct palmas_gpadc *adc, int adc_chan)
{
	palmas_gpadc_start_mask_interrupt(adc, 1);
	palmas_gpadc_enable(adc, adc_chan, false);
}