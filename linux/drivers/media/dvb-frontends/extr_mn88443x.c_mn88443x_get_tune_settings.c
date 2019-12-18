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
struct dvb_frontend_tune_settings {int min_delay_ms; int max_drift; int step_size; } ;
struct dtv_frontend_properties {scalar_t__ delivery_system; } ;
struct dvb_frontend {struct dtv_frontend_properties dtv_property_cache; } ;

/* Variables and functions */
 scalar_t__ SYS_ISDBS ; 
 scalar_t__ SYS_ISDBT ; 

__attribute__((used)) static int mn88443x_get_tune_settings(struct dvb_frontend *fe,
				      struct dvb_frontend_tune_settings *s)
{
	struct dtv_frontend_properties *c = &fe->dtv_property_cache;

	s->min_delay_ms = 850;

	if (c->delivery_system == SYS_ISDBS) {
		s->max_drift = 30000 * 2 + 1;
		s->step_size = 30000;
	} else if (c->delivery_system == SYS_ISDBT) {
		s->max_drift = 142857 * 2 + 1;
		s->step_size = 142857 * 2;
	}

	return 0;
}