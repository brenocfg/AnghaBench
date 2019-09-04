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
typedef  int /*<<< orphan*/  u32 ;
struct mxl5005s_state {struct mxl5005s_config* config; } ;
struct mxl5005s_config {int /*<<< orphan*/  tracking_filter; int /*<<< orphan*/  rssi_enable; int /*<<< orphan*/  cap_select; int /*<<< orphan*/  div_out; int /*<<< orphan*/  clock_out; int /*<<< orphan*/  output_load; int /*<<< orphan*/  top; int /*<<< orphan*/  agc_mode; int /*<<< orphan*/  xtal_freq; int /*<<< orphan*/  if_freq; int /*<<< orphan*/  if_mode; int /*<<< orphan*/  mod_mode; } ;
struct dvb_frontend {struct mxl5005s_state* tuner_priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  InitTunerControls (struct dvb_frontend*) ; 
 int /*<<< orphan*/  MXL5005_TunerConfig (struct dvb_frontend*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mxl5005s_AssignTunerMode(struct dvb_frontend *fe, u32 mod_type,
	u32 bandwidth)
{
	struct mxl5005s_state *state = fe->tuner_priv;
	struct mxl5005s_config *c = state->config;

	InitTunerControls(fe);

	/* Set MxL5005S parameters. */
	MXL5005_TunerConfig(
		fe,
		c->mod_mode,
		c->if_mode,
		bandwidth,
		c->if_freq,
		c->xtal_freq,
		c->agc_mode,
		c->top,
		c->output_load,
		c->clock_out,
		c->div_out,
		c->cap_select,
		c->rssi_enable,
		mod_type,
		c->tracking_filter);

	return 0;
}