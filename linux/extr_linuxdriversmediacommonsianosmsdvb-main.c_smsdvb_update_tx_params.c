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
struct dtv_frontend_properties {int /*<<< orphan*/  modulation; int /*<<< orphan*/  hierarchy; void* code_rate_LP; void* code_rate_HP; int /*<<< orphan*/  guard_interval; int /*<<< orphan*/  transmission_mode; int /*<<< orphan*/  bandwidth_hz; int /*<<< orphan*/  frequency; } ;
struct dvb_frontend {struct dtv_frontend_properties dtv_property_cache; } ;
struct smsdvb_client_t {int /*<<< orphan*/  fe_status; struct dvb_frontend frontend; } ;
struct sms_tx_stats {int /*<<< orphan*/  constellation; int /*<<< orphan*/  hierarchy; int /*<<< orphan*/  lp_code_rate; int /*<<< orphan*/  code_rate; int /*<<< orphan*/  guard_interval; int /*<<< orphan*/  transmission_mode; int /*<<< orphan*/  bandwidth; int /*<<< orphan*/  is_demod_locked; int /*<<< orphan*/  frequency; } ;

/* Variables and functions */
 int /*<<< orphan*/  sms_to_bw (int /*<<< orphan*/ ) ; 
 void* sms_to_code_rate (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sms_to_guard_interval (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sms_to_hierarchy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sms_to_mode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sms_to_modulation (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sms_to_status (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void smsdvb_update_tx_params(struct smsdvb_client_t *client,
				    struct sms_tx_stats *p)
{
	struct dvb_frontend *fe = &client->frontend;
	struct dtv_frontend_properties *c = &fe->dtv_property_cache;

	c->frequency = p->frequency;
	client->fe_status = sms_to_status(p->is_demod_locked, 0);
	c->bandwidth_hz = sms_to_bw(p->bandwidth);
	c->transmission_mode = sms_to_mode(p->transmission_mode);
	c->guard_interval = sms_to_guard_interval(p->guard_interval);
	c->code_rate_HP = sms_to_code_rate(p->code_rate);
	c->code_rate_LP = sms_to_code_rate(p->lp_code_rate);
	c->hierarchy = sms_to_hierarchy(p->hierarchy);
	c->modulation = sms_to_modulation(p->constellation);
}