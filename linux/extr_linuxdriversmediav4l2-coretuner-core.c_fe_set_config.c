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
struct tuner {int dummy; } ;
struct dvb_tuner_ops {int (* set_config ) (struct dvb_frontend*,void*) ;} ;
struct TYPE_2__ {struct dvb_tuner_ops tuner_ops; } ;
struct dvb_frontend {struct tuner* analog_demod_priv; TYPE_1__ ops; } ;

/* Variables and functions */
 int /*<<< orphan*/  pr_warn (char*) ; 
 int stub1 (struct dvb_frontend*,void*) ; 

__attribute__((used)) static int fe_set_config(struct dvb_frontend *fe, void *priv_cfg)
{
	struct dvb_tuner_ops *fe_tuner_ops = &fe->ops.tuner_ops;
	struct tuner *t = fe->analog_demod_priv;

	if (fe_tuner_ops->set_config)
		return fe_tuner_ops->set_config(fe, priv_cfg);

	pr_warn("Tuner frontend module has no way to set config\n");

	return 0;
}