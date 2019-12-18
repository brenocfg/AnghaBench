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
struct dvb_frontend {scalar_t__ exit; struct drx39xxj_state* demodulator_priv; } ;
struct drx_demod_instance {TYPE_1__* my_common_attr; } ;
struct drx39xxj_state {struct drx_demod_instance* demod; } ;
struct TYPE_2__ {int is_opened; } ;

/* Variables and functions */
 scalar_t__ DVB_FE_DEVICE_RESUME ; 
 int /*<<< orphan*/  drx39xxj_set_powerstate (struct dvb_frontend*,int) ; 
 int drxj_open (struct drx_demod_instance*) ; 
 int /*<<< orphan*/  pr_err (char*,int) ; 

__attribute__((used)) static int drx39xxj_init(struct dvb_frontend *fe)
{
	struct drx39xxj_state *state = fe->demodulator_priv;
	struct drx_demod_instance *demod = state->demod;
	int rc = 0;

	if (fe->exit == DVB_FE_DEVICE_RESUME) {
		/* so drxj_open() does what it needs to do */
		demod->my_common_attr->is_opened = false;
		rc = drxj_open(demod);
		if (rc != 0)
			pr_err("drx39xxj_init(): DRX open failed rc=%d!\n", rc);
	} else
		drx39xxj_set_powerstate(fe, 1);

	return rc;
}