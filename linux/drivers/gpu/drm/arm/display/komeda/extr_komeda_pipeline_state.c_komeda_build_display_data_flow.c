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
struct komeda_pipeline {int /*<<< orphan*/  ctrlr; int /*<<< orphan*/  improc; int /*<<< orphan*/  compiz; int /*<<< orphan*/  id; } ;
struct komeda_data_flow_cfg {int dummy; } ;
struct komeda_crtc_state {int /*<<< orphan*/  active_pipes; } ;
struct komeda_crtc {struct komeda_pipeline* slave; struct komeda_pipeline* master; } ;
typedef  int /*<<< orphan*/  s_dflow ;
typedef  int /*<<< orphan*/  m_dflow ;

/* Variables and functions */
 scalar_t__ has_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int komeda_compiz_set_input (int /*<<< orphan*/ ,struct komeda_crtc_state*,struct komeda_data_flow_cfg*) ; 
 int komeda_compiz_validate (int /*<<< orphan*/ ,struct komeda_crtc_state*,struct komeda_data_flow_cfg*) ; 
 int komeda_improc_validate (int /*<<< orphan*/ ,struct komeda_crtc_state*,struct komeda_data_flow_cfg*) ; 
 int komeda_timing_ctrlr_validate (int /*<<< orphan*/ ,struct komeda_crtc_state*,struct komeda_data_flow_cfg*) ; 
 int /*<<< orphan*/  memset (struct komeda_data_flow_cfg*,int /*<<< orphan*/ ,int) ; 

int komeda_build_display_data_flow(struct komeda_crtc *kcrtc,
				   struct komeda_crtc_state *kcrtc_st)
{
	struct komeda_pipeline *master = kcrtc->master;
	struct komeda_pipeline *slave  = kcrtc->slave;
	struct komeda_data_flow_cfg m_dflow; /* master data flow */
	struct komeda_data_flow_cfg s_dflow; /* slave data flow */
	int err;

	memset(&m_dflow, 0, sizeof(m_dflow));
	memset(&s_dflow, 0, sizeof(s_dflow));

	if (slave && has_bit(slave->id, kcrtc_st->active_pipes)) {
		err = komeda_compiz_validate(slave->compiz, kcrtc_st, &s_dflow);
		if (err)
			return err;

		/* merge the slave dflow into master pipeline */
		err = komeda_compiz_set_input(master->compiz, kcrtc_st,
					      &s_dflow);
		if (err)
			return err;
	}

	err = komeda_compiz_validate(master->compiz, kcrtc_st, &m_dflow);
	if (err)
		return err;

	err = komeda_improc_validate(master->improc, kcrtc_st, &m_dflow);
	if (err)
		return err;

	err = komeda_timing_ctrlr_validate(master->ctrlr, kcrtc_st, &m_dflow);
	if (err)
		return err;

	return 0;
}