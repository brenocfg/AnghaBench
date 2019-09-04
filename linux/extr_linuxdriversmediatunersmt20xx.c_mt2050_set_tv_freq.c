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
struct analog_parameters {int std; scalar_t__ mode; int frequency; } ;

/* Variables and functions */
 int V4L2_STD_525_60 ; 
 scalar_t__ V4L2_TUNER_DIGITAL_TV ; 
 int /*<<< orphan*/  mt2050_set_antenna (struct dvb_frontend*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mt2050_set_if_freq (struct dvb_frontend*,int,unsigned int) ; 
 int /*<<< orphan*/  tv_antenna ; 

__attribute__((used)) static int mt2050_set_tv_freq(struct dvb_frontend *fe,
			      struct analog_parameters *params)
{
	unsigned int if2;

	if (params->std & V4L2_STD_525_60) {
		// NTSC
		if2 = 45750*1000;
	} else {
		// PAL
		if2 = 38900*1000;
	}
	if (V4L2_TUNER_DIGITAL_TV == params->mode) {
		// DVB (pinnacle 300i)
		if2 = 36150*1000;
	}
	mt2050_set_if_freq(fe, params->frequency*62500, if2);
	mt2050_set_antenna(fe, tv_antenna);

	return 0;
}