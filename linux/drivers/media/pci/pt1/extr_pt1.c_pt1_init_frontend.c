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
struct pt1_adapter {struct dvb_frontend* fe; int /*<<< orphan*/  adap; int /*<<< orphan*/  orig_init; int /*<<< orphan*/  orig_sleep; int /*<<< orphan*/  orig_set_voltage; } ;
struct TYPE_2__ {int /*<<< orphan*/  init; int /*<<< orphan*/  sleep; int /*<<< orphan*/  set_voltage; } ;
struct dvb_frontend {TYPE_1__ ops; } ;

/* Variables and functions */
 int dvb_register_frontend (int /*<<< orphan*/ *,struct dvb_frontend*) ; 
 int /*<<< orphan*/  pt1_set_voltage ; 
 int /*<<< orphan*/  pt1_sleep ; 
 int /*<<< orphan*/  pt1_wakeup ; 

__attribute__((used)) static int pt1_init_frontend(struct pt1_adapter *adap, struct dvb_frontend *fe)
{
	int ret;

	adap->orig_set_voltage = fe->ops.set_voltage;
	adap->orig_sleep = fe->ops.sleep;
	adap->orig_init = fe->ops.init;
	fe->ops.set_voltage = pt1_set_voltage;
	fe->ops.sleep = pt1_sleep;
	fe->ops.init = pt1_wakeup;

	ret = dvb_register_frontend(&adap->adap, fe);
	if (ret < 0)
		return ret;

	adap->fe = fe;
	return 0;
}