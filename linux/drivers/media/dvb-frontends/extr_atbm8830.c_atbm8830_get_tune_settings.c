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
struct dvb_frontend_tune_settings {scalar_t__ max_drift; scalar_t__ step_size; scalar_t__ min_delay_ms; } ;
struct dvb_frontend {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static int atbm8830_get_tune_settings(struct dvb_frontend *fe,
	struct dvb_frontend_tune_settings *fesettings)
{
	fesettings->min_delay_ms = 0;
	fesettings->step_size = 0;
	fesettings->max_drift = 0;
	return 0;
}