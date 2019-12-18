#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct dvb_frontend {struct dib8000_state* demodulator_priv; } ;
struct TYPE_10__ {int len; TYPE_4__* stat; } ;
struct TYPE_8__ {int len; TYPE_2__* stat; } ;
struct dtv_frontend_properties {TYPE_5__ post_bit_count; TYPE_5__ post_bit_error; TYPE_3__ block_count; TYPE_5__ block_error; TYPE_5__ cnr; TYPE_5__ strength; } ;
struct dib8000_state {TYPE_5__ ber_jiffies_stats_layer; scalar_t__ per_jiffies_stats; scalar_t__ ber_jiffies_stats; int /*<<< orphan*/  init_ucb; TYPE_1__** fe; } ;
struct TYPE_9__ {void* scale; scalar_t__ uvalue; } ;
struct TYPE_7__ {void* scale; } ;
struct TYPE_6__ {struct dtv_frontend_properties dtv_property_cache; } ;

/* Variables and functions */
 void* FE_SCALE_DECIBEL ; 
 void* FE_SCALE_NOT_AVAILABLE ; 
 int /*<<< orphan*/  dib8000_read_unc_blocks (struct dvb_frontend*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (TYPE_5__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void dib8000_reset_stats(struct dvb_frontend *fe)
{
	struct dib8000_state *state = fe->demodulator_priv;
	struct dtv_frontend_properties *c = &state->fe[0]->dtv_property_cache;
	u32 ucb;

	memset(&c->strength, 0, sizeof(c->strength));
	memset(&c->cnr, 0, sizeof(c->cnr));
	memset(&c->post_bit_error, 0, sizeof(c->post_bit_error));
	memset(&c->post_bit_count, 0, sizeof(c->post_bit_count));
	memset(&c->block_error, 0, sizeof(c->block_error));

	c->strength.len = 1;
	c->cnr.len = 1;
	c->block_error.len = 1;
	c->block_count.len = 1;
	c->post_bit_error.len = 1;
	c->post_bit_count.len = 1;

	c->strength.stat[0].scale = FE_SCALE_DECIBEL;
	c->strength.stat[0].uvalue = 0;

	c->cnr.stat[0].scale = FE_SCALE_NOT_AVAILABLE;
	c->block_error.stat[0].scale = FE_SCALE_NOT_AVAILABLE;
	c->block_count.stat[0].scale = FE_SCALE_NOT_AVAILABLE;
	c->post_bit_error.stat[0].scale = FE_SCALE_NOT_AVAILABLE;
	c->post_bit_count.stat[0].scale = FE_SCALE_NOT_AVAILABLE;

	dib8000_read_unc_blocks(fe, &ucb);

	state->init_ucb = -ucb;
	state->ber_jiffies_stats = 0;
	state->per_jiffies_stats = 0;
	memset(&state->ber_jiffies_stats_layer, 0,
	       sizeof(state->ber_jiffies_stats_layer));
}