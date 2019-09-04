#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  int u16 ;
struct TYPE_3__ {int /*<<< orphan*/ * release; } ;
struct TYPE_4__ {TYPE_1__ tuner_ops; } ;
struct dvb_frontend {TYPE_2__ ops; struct af9005_fe_state* demodulator_priv; } ;
struct af9005_fe_state {int /*<<< orphan*/  d; } ;

/* Variables and functions */
 int ENODEV ; 
 int af9005_read_ofdm_register (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  xd_r_reg_aagc_if_gain ; 
 int /*<<< orphan*/  xd_r_reg_aagc_rf_gain ; 

__attribute__((used)) static int af9005_fe_read_signal_strength(struct dvb_frontend *fe,
					  u16 * strength)
{
	struct af9005_fe_state *state = fe->demodulator_priv;
	int ret;
	u8 if_gain, rf_gain;

	if (fe->ops.tuner_ops.release == NULL)
		return -ENODEV;
	ret =
	    af9005_read_ofdm_register(state->d, xd_r_reg_aagc_rf_gain,
				      &rf_gain);
	if (ret)
		return ret;
	ret =
	    af9005_read_ofdm_register(state->d, xd_r_reg_aagc_if_gain,
				      &if_gain);
	if (ret)
		return ret;
	/* this value has no real meaning, but i don't have the tables that relate
	   the rf and if gain with the dbm, so I just scale the value */
	*strength = (512 - rf_gain - if_gain) << 7;
	return 0;
}