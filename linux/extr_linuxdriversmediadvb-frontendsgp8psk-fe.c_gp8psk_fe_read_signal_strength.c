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
struct gp8psk_fe_state {int snr; } ;
struct dvb_frontend {struct gp8psk_fe_state* demodulator_priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  gp8psk_fe_update_status (struct gp8psk_fe_state*) ; 

__attribute__((used)) static int gp8psk_fe_read_signal_strength(struct dvb_frontend* fe, u16 *strength)
{
	struct gp8psk_fe_state *st = fe->demodulator_priv;
	gp8psk_fe_update_status(st);
	/* snr is reported in dBu*256 */
	/* snr / 38.4 ~= 100% strength */
	/* snr * 17 returns 100% strength as 65535 */
	if (st->snr > 0xf00)
		*strength = 0xffff;
	else
		*strength = (st->snr << 4) + st->snr; /* snr*17 */
	return 0;
}