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
struct isl6423_dev {int reg_3; int reg_4; int /*<<< orphan*/  verbose; struct i2c_adapter* i2c; struct isl6423_config const* config; } ;
struct isl6423_config {int dummy; } ;
struct i2c_adapter {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  enable_high_lnb_voltage; int /*<<< orphan*/  set_voltage; int /*<<< orphan*/  release_sec; } ;
struct dvb_frontend {struct isl6423_dev* sec_priv; TYPE_1__ ops; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  isl6423_release ; 
 scalar_t__ isl6423_set_current (struct dvb_frontend*) ; 
 scalar_t__ isl6423_set_modulation (struct dvb_frontend*) ; 
 int /*<<< orphan*/  isl6423_set_voltage ; 
 int /*<<< orphan*/  isl6423_voltage_boost ; 
 int /*<<< orphan*/  kfree (struct isl6423_dev*) ; 
 struct isl6423_dev* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  verbose ; 

struct dvb_frontend *isl6423_attach(struct dvb_frontend *fe,
				    struct i2c_adapter *i2c,
				    const struct isl6423_config *config)
{
	struct isl6423_dev *isl6423;

	isl6423 = kzalloc(sizeof(struct isl6423_dev), GFP_KERNEL);
	if (!isl6423)
		return NULL;

	isl6423->config	= config;
	isl6423->i2c	= i2c;
	fe->sec_priv	= isl6423;

	/* SR3H = 0, SR3M = 1, SR3L = 0 */
	isl6423->reg_3 = 0x02 << 5;
	/* SR4H = 0, SR4M = 1, SR4L = 1 */
	isl6423->reg_4 = 0x03 << 5;

	if (isl6423_set_current(fe))
		goto exit;

	if (isl6423_set_modulation(fe))
		goto exit;

	fe->ops.release_sec		= isl6423_release;
	fe->ops.set_voltage		= isl6423_set_voltage;
	fe->ops.enable_high_lnb_voltage = isl6423_voltage_boost;
	isl6423->verbose		= verbose;

	return fe;

exit:
	kfree(isl6423);
	fe->sec_priv = NULL;
	return NULL;
}