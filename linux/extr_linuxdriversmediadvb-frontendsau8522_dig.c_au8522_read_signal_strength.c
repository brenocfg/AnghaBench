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
typedef  int u32 ;
typedef  int u16 ;
struct dvb_frontend {int dummy; } ;

/* Variables and functions */
 int au8522_read_snr (struct dvb_frontend*,int*) ; 

__attribute__((used)) static int au8522_read_signal_strength(struct dvb_frontend *fe,
				       u16 *signal_strength)
{
	/* borrowed from lgdt330x.c
	 *
	 * Calculate strength from SNR up to 35dB
	 * Even though the SNR can go higher than 35dB,
	 * there is some comfort factor in having a range of
	 * strong signals that can show at 100%
	 */
	u16 snr;
	u32 tmp;
	int ret = au8522_read_snr(fe, &snr);

	*signal_strength = 0;

	if (0 == ret) {
		/* The following calculation method was chosen
		 * purely for the sake of code re-use from the
		 * other demod drivers that use this method */

		/* Convert from SNR in dB * 10 to 8.24 fixed-point */
		tmp = (snr * ((1 << 24) / 10));

		/* Convert from 8.24 fixed-point to
		 * scale the range 0 - 35*2^24 into 0 - 65535*/
		if (tmp >= 8960 * 0x10000)
			*signal_strength = 0xffff;
		else
			*signal_strength = tmp / 8960;
	}

	return ret;
}