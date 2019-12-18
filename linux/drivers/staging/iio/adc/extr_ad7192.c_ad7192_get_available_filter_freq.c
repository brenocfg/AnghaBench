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
struct ad7192_state {unsigned int fclk; int /*<<< orphan*/  mode; } ;

/* Variables and functions */
 int AD7192_MODE_RATE (int /*<<< orphan*/ ) ; 
 int AD7192_SYNC3_FILTER ; 
 int AD7192_SYNC4_FILTER ; 
 void* DIV_ROUND_CLOSEST (unsigned int,int) ; 

__attribute__((used)) static void ad7192_get_available_filter_freq(struct ad7192_state *st,
						    int *freq)
{
	unsigned int fadc;

	/* Formulas for filter at page 25 of the datasheet */
	fadc = DIV_ROUND_CLOSEST(st->fclk,
				 AD7192_SYNC4_FILTER * AD7192_MODE_RATE(st->mode));
	freq[0] = DIV_ROUND_CLOSEST(fadc * 240, 1024);

	fadc = DIV_ROUND_CLOSEST(st->fclk,
				 AD7192_SYNC3_FILTER * AD7192_MODE_RATE(st->mode));
	freq[1] = DIV_ROUND_CLOSEST(fadc * 240, 1024);

	fadc = DIV_ROUND_CLOSEST(st->fclk, AD7192_MODE_RATE(st->mode));
	freq[2] = DIV_ROUND_CLOSEST(fadc * 230, 1024);
	freq[3] = DIV_ROUND_CLOSEST(fadc * 272, 1024);
}