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
typedef  int u8 ;
typedef  int u16 ;
struct or51211_state {int snr; TYPE_1__* config; } ;
struct dvb_frontend {struct or51211_state* demodulator_priv; } ;
struct TYPE_2__ {int /*<<< orphan*/  demod_address; } ;

/* Variables and functions */
 int calculate_snr (int,int) ; 
 int /*<<< orphan*/  dprintk (char*,int,int,int) ; 
 scalar_t__ i2c_readbytes (struct or51211_state*,int /*<<< orphan*/ ,int*,int) ; 
 scalar_t__ i2c_writebytes (struct or51211_state*,int /*<<< orphan*/ ,int*,int) ; 
 int /*<<< orphan*/  pr_warn (char*) ; 

__attribute__((used)) static int or51211_read_snr(struct dvb_frontend* fe, u16* snr)
{
	struct or51211_state* state = fe->demodulator_priv;
	u8 rec_buf[2];
	u8 snd_buf[3];

	/* SNR after Equalizer */
	snd_buf[0] = 0x04;
	snd_buf[1] = 0x00;
	snd_buf[2] = 0x04;

	if (i2c_writebytes(state,state->config->demod_address,snd_buf,3)) {
		pr_warn("error writing snr reg\n");
		return -1;
	}
	if (i2c_readbytes(state,state->config->demod_address,rec_buf,2)) {
		pr_warn("read_status read error\n");
		return -1;
	}

	state->snr = calculate_snr(rec_buf[0], 89599047);
	*snr = (state->snr) >> 16;

	dprintk("noise = 0x%02x, snr = %d.%02d dB\n", rec_buf[0],
		state->snr >> 24, (((state->snr>>8) & 0xffff) * 100) >> 16);

	return 0;
}