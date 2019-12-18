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
struct vp7045_fe_state {int /*<<< orphan*/  d; } ;
struct dvb_frontend {struct vp7045_fe_state* demodulator_priv; } ;

/* Variables and functions */
 int vp7045_read_reg (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int vp7045_fe_read_signal_strength(struct dvb_frontend* fe, u16 *strength)
{
	struct vp7045_fe_state *state = fe->demodulator_priv;
	u16 signal = (vp7045_read_reg(state->d, 0x14) << 8) |
		vp7045_read_reg(state->d, 0x15);

	*strength = ~signal;
	return 0;
}