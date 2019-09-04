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
struct dvb_frontend_tune_settings {int min_delay_ms; int step_size; int max_drift; } ;
struct dtv_frontend_properties {int symbol_rate; } ;
struct dvb_frontend {struct dtv_frontend_properties dtv_property_cache; } ;

/* Variables and functions */

__attribute__((used)) static int s5h1420_get_tune_settings(struct dvb_frontend* fe,
				     struct dvb_frontend_tune_settings* fesettings)
{
	struct dtv_frontend_properties *p = &fe->dtv_property_cache;
	if (p->symbol_rate > 20000000) {
		fesettings->min_delay_ms = 50;
		fesettings->step_size = 2000;
		fesettings->max_drift = 8000;
	} else if (p->symbol_rate > 12000000) {
		fesettings->min_delay_ms = 100;
		fesettings->step_size = 1500;
		fesettings->max_drift = 9000;
	} else if (p->symbol_rate > 8000000) {
		fesettings->min_delay_ms = 100;
		fesettings->step_size = 1000;
		fesettings->max_drift = 8000;
	} else if (p->symbol_rate > 4000000) {
		fesettings->min_delay_ms = 100;
		fesettings->step_size = 500;
		fesettings->max_drift = 7000;
	} else if (p->symbol_rate > 2000000) {
		fesettings->min_delay_ms = 200;
		fesettings->step_size = (p->symbol_rate / 8000);
		fesettings->max_drift = 14 * fesettings->step_size;
	} else {
		fesettings->min_delay_ms = 200;
		fesettings->step_size = (p->symbol_rate / 8000);
		fesettings->max_drift = 18 * fesettings->step_size;
	}

	return 0;
}