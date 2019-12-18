#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_24__   TYPE_9__ ;
typedef  struct TYPE_23__   TYPE_8__ ;
typedef  struct TYPE_22__   TYPE_7__ ;
typedef  struct TYPE_21__   TYPE_6__ ;
typedef  struct TYPE_20__   TYPE_5__ ;
typedef  struct TYPE_19__   TYPE_4__ ;
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;
typedef  struct TYPE_15__   TYPE_12__ ;
typedef  struct TYPE_14__   TYPE_11__ ;
typedef  struct TYPE_13__   TYPE_10__ ;

/* Type definitions */
struct TYPE_15__ {TYPE_11__* stat; } ;
struct TYPE_13__ {TYPE_9__* stat; } ;
struct TYPE_23__ {TYPE_7__* stat; } ;
struct TYPE_21__ {TYPE_5__* stat; } ;
struct TYPE_19__ {TYPE_3__* stat; } ;
struct TYPE_17__ {TYPE_1__* stat; } ;
struct dtv_frontend_properties {int lna; TYPE_12__ post_bit_count; TYPE_10__ post_bit_error; TYPE_8__ block_count; TYPE_6__ block_error; TYPE_4__ strength; TYPE_2__ cnr; int /*<<< orphan*/  modulation; int /*<<< orphan*/  hierarchy; void* code_rate_LP; void* code_rate_HP; int /*<<< orphan*/  guard_interval; int /*<<< orphan*/  transmission_mode; int /*<<< orphan*/  bandwidth_hz; int /*<<< orphan*/  frequency; } ;
struct dvb_frontend {struct dtv_frontend_properties dtv_property_cache; } ;
struct smsdvb_client_t {int /*<<< orphan*/  legacy_ber; int /*<<< orphan*/  last_per; void* fe_status; int /*<<< orphan*/  debug_data; int /*<<< orphan*/  (* prt_dvb_stats ) (int /*<<< orphan*/ ,struct sms_stats*) ;struct dvb_frontend frontend; } ;
struct sms_stats {int SNR; int in_band_pwr; int /*<<< orphan*/  ber; scalar_t__ ber_bit_count; scalar_t__ ber_error_count; scalar_t__ total_ts_packets; scalar_t__ error_ts_packets; int /*<<< orphan*/  is_demod_locked; scalar_t__ is_external_lna_on; int /*<<< orphan*/  constellation; int /*<<< orphan*/  hierarchy; int /*<<< orphan*/  lp_code_rate; int /*<<< orphan*/  code_rate; int /*<<< orphan*/  guard_interval; int /*<<< orphan*/  transmission_mode; int /*<<< orphan*/  bandwidth; int /*<<< orphan*/  frequency; int /*<<< orphan*/  is_rf_locked; } ;
struct TYPE_24__ {int /*<<< orphan*/  uvalue; void* scale; } ;
struct TYPE_22__ {int /*<<< orphan*/  uvalue; void* scale; } ;
struct TYPE_20__ {int /*<<< orphan*/  uvalue; void* scale; } ;
struct TYPE_18__ {int uvalue; } ;
struct TYPE_16__ {int svalue; } ;
struct TYPE_14__ {int /*<<< orphan*/  uvalue; void* scale; } ;

/* Variables and functions */
 void* FE_SCALE_COUNTER ; 
 int /*<<< orphan*/  sms_to_bw (int /*<<< orphan*/ ) ; 
 void* sms_to_code_rate (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sms_to_guard_interval (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sms_to_hierarchy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sms_to_mode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sms_to_modulation (int /*<<< orphan*/ ) ; 
 void* sms_to_status (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,struct sms_stats*) ; 

__attribute__((used)) static void smsdvb_update_dvb_stats(struct smsdvb_client_t *client,
				    struct sms_stats *p)
{
	struct dvb_frontend *fe = &client->frontend;
	struct dtv_frontend_properties *c = &fe->dtv_property_cache;

	if (client->prt_dvb_stats)
		client->prt_dvb_stats(client->debug_data, p);

	client->fe_status = sms_to_status(p->is_demod_locked, p->is_rf_locked);

	/* Update DVB modulation parameters */
	c->frequency = p->frequency;
	client->fe_status = sms_to_status(p->is_demod_locked, 0);
	c->bandwidth_hz = sms_to_bw(p->bandwidth);
	c->transmission_mode = sms_to_mode(p->transmission_mode);
	c->guard_interval = sms_to_guard_interval(p->guard_interval);
	c->code_rate_HP = sms_to_code_rate(p->code_rate);
	c->code_rate_LP = sms_to_code_rate(p->lp_code_rate);
	c->hierarchy = sms_to_hierarchy(p->hierarchy);
	c->modulation = sms_to_modulation(p->constellation);

	/* update reception data */
	c->lna = p->is_external_lna_on ? 1 : 0;

	/* Carrier to noise ratio, in DB */
	c->cnr.stat[0].svalue = p->SNR * 1000;

	/* signal Strength, in DBm */
	c->strength.stat[0].uvalue = p->in_band_pwr * 1000;

	/* PER/BER requires demod lock */
	if (!p->is_demod_locked)
		return;

	/* TS PER */
	client->last_per = c->block_error.stat[0].uvalue;
	c->block_error.stat[0].scale = FE_SCALE_COUNTER;
	c->block_count.stat[0].scale = FE_SCALE_COUNTER;
	c->block_error.stat[0].uvalue += p->error_ts_packets;
	c->block_count.stat[0].uvalue += p->total_ts_packets;

	/* ber */
	c->post_bit_error.stat[0].scale = FE_SCALE_COUNTER;
	c->post_bit_count.stat[0].scale = FE_SCALE_COUNTER;
	c->post_bit_error.stat[0].uvalue += p->ber_error_count;
	c->post_bit_count.stat[0].uvalue += p->ber_bit_count;

	/* Legacy PER/BER */
	client->legacy_ber = p->ber;
}