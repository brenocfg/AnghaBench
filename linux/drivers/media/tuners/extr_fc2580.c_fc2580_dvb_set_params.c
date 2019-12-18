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
struct fc2580_dev {int /*<<< orphan*/  f_bandwidth; int /*<<< orphan*/  f_frequency; } ;
struct dtv_frontend_properties {int /*<<< orphan*/  bandwidth_hz; int /*<<< orphan*/  frequency; } ;
struct dvb_frontend {struct dtv_frontend_properties dtv_property_cache; struct fc2580_dev* tuner_priv; } ;

/* Variables and functions */
 int fc2580_set_params (struct fc2580_dev*) ; 

__attribute__((used)) static int fc2580_dvb_set_params(struct dvb_frontend *fe)
{
	struct fc2580_dev *dev = fe->tuner_priv;
	struct dtv_frontend_properties *c = &fe->dtv_property_cache;

	dev->f_frequency = c->frequency;
	dev->f_bandwidth = c->bandwidth_hz;
	return fc2580_set_params(dev);
}