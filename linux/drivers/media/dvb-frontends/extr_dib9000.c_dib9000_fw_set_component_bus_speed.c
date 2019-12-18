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
typedef  int /*<<< orphan*/  u16 ;
struct dvb_frontend {struct dib9000_state* demodulator_priv; } ;
struct dib9000_state {int /*<<< orphan*/  component_bus_speed; } ;

/* Variables and functions */

int dib9000_fw_set_component_bus_speed(struct dvb_frontend *fe, u16 speed)
{
	struct dib9000_state *state = fe->demodulator_priv;

	state->component_bus_speed = speed;
	return 0;
}