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
struct dvb_frontend_tune_settings {int min_delay_ms; int /*<<< orphan*/  step_size; int /*<<< orphan*/  max_drift; } ;
struct dtv_frontend_properties {int delivery_system; } ;
struct dvb_frontend {struct dtv_frontend_properties dtv_property_cache; struct drxk_state* demodulator_priv; } ;
struct drxk_state {scalar_t__ m_drxk_state; } ;

/* Variables and functions */
 scalar_t__ DRXK_NO_DEV ; 
 scalar_t__ DRXK_UNINITIALIZED ; 
 int EAGAIN ; 
 int EINVAL ; 
 int ENODEV ; 
#define  SYS_DVBC_ANNEX_A 130 
#define  SYS_DVBC_ANNEX_C 129 
#define  SYS_DVBT 128 
 int /*<<< orphan*/  dprintk (int,char*) ; 

__attribute__((used)) static int drxk_get_tune_settings(struct dvb_frontend *fe,
				  struct dvb_frontend_tune_settings *sets)
{
	struct drxk_state *state = fe->demodulator_priv;
	struct dtv_frontend_properties *p = &fe->dtv_property_cache;

	dprintk(1, "\n");

	if (state->m_drxk_state == DRXK_NO_DEV)
		return -ENODEV;
	if (state->m_drxk_state == DRXK_UNINITIALIZED)
		return -EAGAIN;

	switch (p->delivery_system) {
	case SYS_DVBC_ANNEX_A:
	case SYS_DVBC_ANNEX_C:
	case SYS_DVBT:
		sets->min_delay_ms = 3000;
		sets->max_drift = 0;
		sets->step_size = 0;
		return 0;
	default:
		return -EINVAL;
	}
}