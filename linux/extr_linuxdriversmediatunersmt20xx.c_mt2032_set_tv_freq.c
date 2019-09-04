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
struct dvb_frontend {int dummy; } ;
struct analog_parameters {int std; int frequency; } ;

/* Variables and functions */
 int V4L2_STD_525_60 ; 
 int /*<<< orphan*/  mt2032_set_if_freq (struct dvb_frontend*,int,int,int,int,int) ; 

__attribute__((used)) static int mt2032_set_tv_freq(struct dvb_frontend *fe,
			      struct analog_parameters *params)
{
	int if2,from,to;

	// signal bandwidth and picture carrier
	if (params->std & V4L2_STD_525_60) {
		// NTSC
		from = 40750*1000;
		to   = 46750*1000;
		if2  = 45750*1000;
	} else {
		// PAL
		from = 32900*1000;
		to   = 39900*1000;
		if2  = 38900*1000;
	}

	mt2032_set_if_freq(fe, params->frequency*62500,
			   1090*1000*1000, if2, from, to);

	return 0;
}