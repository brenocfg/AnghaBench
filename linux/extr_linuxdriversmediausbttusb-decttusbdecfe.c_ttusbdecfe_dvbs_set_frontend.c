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
typedef  int /*<<< orphan*/  u32 ;
struct ttusbdecfe_state {TYPE_1__* config; scalar_t__ voltage; scalar_t__ hi_band; } ;
struct dtv_frontend_properties {scalar_t__ symbol_rate; scalar_t__ frequency; } ;
struct dvb_frontend {scalar_t__ demodulator_priv; struct dtv_frontend_properties dtv_property_cache; } ;
typedef  int /*<<< orphan*/  b ;
typedef  int /*<<< orphan*/  __be32 ;
struct TYPE_2__ {int /*<<< orphan*/  (* send_command ) (struct dvb_frontend*,int,int,int*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 scalar_t__ LOF_HI ; 
 scalar_t__ LOF_LO ; 
 int /*<<< orphan*/  htonl (scalar_t__) ; 
 int /*<<< orphan*/  memcpy (int*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  stub1 (struct dvb_frontend*,int,int,int*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ttusbdecfe_dvbs_set_frontend(struct dvb_frontend *fe)
{
	struct dtv_frontend_properties *p = &fe->dtv_property_cache;
	struct ttusbdecfe_state* state = (struct ttusbdecfe_state*) fe->demodulator_priv;

	u8 b[] = { 0x00, 0x00, 0x00, 0x01,
		   0x00, 0x00, 0x00, 0x00,
		   0x00, 0x00, 0x00, 0x01,
		   0x00, 0x00, 0x00, 0x00,
		   0x00, 0x00, 0x00, 0x00,
		   0x00, 0x00, 0x00, 0x00,
		   0x00, 0x00, 0x00, 0x00,
		   0x00, 0x00, 0x00, 0x00,
		   0x00, 0x00, 0x00, 0x00,
		   0x00, 0x00, 0x00, 0x00 };
	__be32 freq;
	__be32 sym_rate;
	__be32 band;
	__be32 lnb_voltage;

	freq = htonl(p->frequency +
	       (state->hi_band ? LOF_HI : LOF_LO));
	memcpy(&b[4], &freq, sizeof(u32));
	sym_rate = htonl(p->symbol_rate);
	memcpy(&b[12], &sym_rate, sizeof(u32));
	band = htonl(state->hi_band ? LOF_HI : LOF_LO);
	memcpy(&b[24], &band, sizeof(u32));
	lnb_voltage = htonl(state->voltage);
	memcpy(&b[28], &lnb_voltage, sizeof(u32));

	state->config->send_command(fe, 0x71, sizeof(b), b, NULL, NULL);

	return 0;
}