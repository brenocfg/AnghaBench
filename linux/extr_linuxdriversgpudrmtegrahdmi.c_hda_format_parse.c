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
 unsigned int AC_FMT_BASE_44K ; 
 unsigned int AC_FMT_CHAN_MASK ; 
 unsigned int AC_FMT_CHAN_SHIFT ; 
 unsigned int AC_FMT_DIV_MASK ; 
 unsigned int AC_FMT_DIV_SHIFT ; 
 unsigned int AC_FMT_MULT_MASK ; 
 unsigned int AC_FMT_MULT_SHIFT ; 

__attribute__((used)) static void hda_format_parse(unsigned int format, unsigned int *rate,
			     unsigned int *channels)
{
	unsigned int mul, div;

	if (format & AC_FMT_BASE_44K)
		*rate = 44100;
	else
		*rate = 48000;

	mul = (format & AC_FMT_MULT_MASK) >> AC_FMT_MULT_SHIFT;
	div = (format & AC_FMT_DIV_MASK) >> AC_FMT_DIV_SHIFT;

	*rate = *rate * (mul + 1) / (div + 1);

	*channels = (format & AC_FMT_CHAN_MASK) >> AC_FMT_CHAN_SHIFT;
}