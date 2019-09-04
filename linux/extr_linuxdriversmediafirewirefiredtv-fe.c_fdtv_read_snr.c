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
typedef  int u16 ;
struct firedtv_tuner_status {int carrier_noise_ratio; } ;
struct firedtv {int dummy; } ;
struct dvb_frontend {struct firedtv* sec_priv; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ avc_tuner_status (struct firedtv*,struct firedtv_tuner_status*) ; 

__attribute__((used)) static int fdtv_read_snr(struct dvb_frontend *fe, u16 *snr)
{
	struct firedtv *fdtv = fe->sec_priv;
	struct firedtv_tuner_status stat;

	if (avc_tuner_status(fdtv, &stat))
		return -EINVAL;

	/* C/N[dB] = -10 * log10(snr / 65535) */
	*snr = stat.carrier_noise_ratio * 257;
	return 0;
}