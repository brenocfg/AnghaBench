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
struct dvb_frontend {struct drxk_state* demodulator_priv; } ;
struct drxk_state {scalar_t__ m_drxk_state; } ;

/* Variables and functions */
 int ConfigureI2CBridge (struct drxk_state*,int) ; 
 scalar_t__ DRXK_NO_DEV ; 
 int ENODEV ; 
 int /*<<< orphan*/  dprintk (int,char*,char*) ; 

__attribute__((used)) static int drxk_gate_ctrl(struct dvb_frontend *fe, int enable)
{
	struct drxk_state *state = fe->demodulator_priv;

	dprintk(1, ": %s\n", enable ? "enable" : "disable");

	if (state->m_drxk_state == DRXK_NO_DEV)
		return -ENODEV;

	return ConfigureI2CBridge(state, enable ? true : false);
}