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
struct ad7192_state {unsigned int fclk; int f_order; int mode; int conf; } ;

/* Variables and functions */
 int AD7192_CONF_CHOP ; 
 int AD7192_MODE_RATE (int) ; 
 int AD7192_MODE_SINC3 ; 
 int DIV_ROUND_CLOSEST (unsigned int,int) ; 

__attribute__((used)) static int ad7192_get_3db_filter_freq(struct ad7192_state *st)
{
	unsigned int fadc;

	fadc = DIV_ROUND_CLOSEST(st->fclk,
				 st->f_order * AD7192_MODE_RATE(st->mode));

	if (st->conf & AD7192_CONF_CHOP)
		return DIV_ROUND_CLOSEST(fadc * 240, 1024);
	if (st->mode & AD7192_MODE_SINC3)
		return DIV_ROUND_CLOSEST(fadc * 272, 1024);
	else
		return DIV_ROUND_CLOSEST(fadc * 230, 1024);
}