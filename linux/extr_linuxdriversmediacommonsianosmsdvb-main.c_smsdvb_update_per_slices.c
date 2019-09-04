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
typedef  unsigned long long u64 ;
struct TYPE_15__ {TYPE_11__* stat; } ;
struct TYPE_13__ {TYPE_9__* stat; } ;
struct TYPE_23__ {TYPE_7__* stat; } ;
struct TYPE_21__ {TYPE_5__* stat; } ;
struct TYPE_19__ {TYPE_3__* stat; } ;
struct TYPE_17__ {TYPE_1__* stat; } ;
struct dtv_frontend_properties {TYPE_12__ post_bit_count; TYPE_10__ post_bit_error; TYPE_8__ block_count; TYPE_6__ block_error; TYPE_4__ cnr; TYPE_2__ strength; int /*<<< orphan*/  modulation; } ;
struct dvb_frontend {struct dtv_frontend_properties dtv_property_cache; } ;
struct smsdvb_client_t {unsigned long long legacy_per; int /*<<< orphan*/  last_per; int /*<<< orphan*/  fe_status; struct dvb_frontend frontend; } ;
struct RECEPTION_STATISTICS_PER_SLICES_S {int in_band_power; int snr; unsigned long long ets_packets; unsigned long long ts_packets; scalar_t__ ber_bit_count; scalar_t__ ber_error_count; int /*<<< orphan*/  is_demod_locked; int /*<<< orphan*/  constellation; int /*<<< orphan*/  is_rf_locked; } ;
struct TYPE_24__ {int /*<<< orphan*/  uvalue; void* scale; } ;
struct TYPE_22__ {int /*<<< orphan*/  uvalue; void* scale; } ;
struct TYPE_20__ {int /*<<< orphan*/  uvalue; void* scale; } ;
struct TYPE_18__ {int svalue; } ;
struct TYPE_16__ {int uvalue; } ;
struct TYPE_14__ {int /*<<< orphan*/  uvalue; void* scale; } ;

/* Variables and functions */
 void* FE_SCALE_COUNTER ; 
 int /*<<< orphan*/  do_div (unsigned long long,unsigned long long) ; 
 int /*<<< orphan*/  sms_to_modulation (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sms_to_status (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void smsdvb_update_per_slices(struct smsdvb_client_t *client,
				     struct RECEPTION_STATISTICS_PER_SLICES_S *p)
{
	struct dvb_frontend *fe = &client->frontend;
	struct dtv_frontend_properties *c = &fe->dtv_property_cache;
	u64 tmp;

	client->fe_status = sms_to_status(p->is_demod_locked, p->is_rf_locked);
	c->modulation = sms_to_modulation(p->constellation);

	/* signal Strength, in DBm */
	c->strength.stat[0].uvalue = p->in_band_power * 1000;

	/* Carrier to noise ratio, in DB */
	c->cnr.stat[0].svalue = p->snr * 1000;

	/* PER/BER requires demod lock */
	if (!p->is_demod_locked)
		return;

	/* TS PER */
	client->last_per = c->block_error.stat[0].uvalue;
	c->block_error.stat[0].scale = FE_SCALE_COUNTER;
	c->block_count.stat[0].scale = FE_SCALE_COUNTER;
	c->block_error.stat[0].uvalue += p->ets_packets;
	c->block_count.stat[0].uvalue += p->ets_packets + p->ts_packets;

	/* ber */
	c->post_bit_error.stat[0].scale = FE_SCALE_COUNTER;
	c->post_bit_count.stat[0].scale = FE_SCALE_COUNTER;
	c->post_bit_error.stat[0].uvalue += p->ber_error_count;
	c->post_bit_count.stat[0].uvalue += p->ber_bit_count;

	/* Legacy PER/BER */
	tmp = p->ets_packets * 65535ULL;
	if (p->ts_packets + p->ets_packets)
		do_div(tmp, p->ts_packets + p->ets_packets);
	client->legacy_per = tmp;
}