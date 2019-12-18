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
typedef  int u8 ;
struct isl6405 {int i2c_addr; int override_or; int override_and; struct i2c_adapter* i2c; int /*<<< orphan*/  config; } ;
struct i2c_adapter {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  enable_high_lnb_voltage; scalar_t__ (* set_voltage ) (struct dvb_frontend*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  release_sec; } ;
struct dvb_frontend {TYPE_1__ ops; struct isl6405* sec_priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  ISL6405_ISEL1 ; 
 int /*<<< orphan*/  ISL6405_ISEL2 ; 
 int /*<<< orphan*/  SEC_VOLTAGE_OFF ; 
 int /*<<< orphan*/  isl6405_enable_high_lnb_voltage ; 
 int /*<<< orphan*/  isl6405_release ; 
 scalar_t__ isl6405_set_voltage (struct dvb_frontend*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct isl6405*) ; 
 struct isl6405* kmalloc (int,int /*<<< orphan*/ ) ; 

struct dvb_frontend *isl6405_attach(struct dvb_frontend *fe, struct i2c_adapter *i2c,
				    u8 i2c_addr, u8 override_set, u8 override_clear)
{
	struct isl6405 *isl6405 = kmalloc(sizeof(struct isl6405), GFP_KERNEL);
	if (!isl6405)
		return NULL;

	/* default configuration */
	if (override_set & 0x80)
		isl6405->config = ISL6405_ISEL2;
	else
		isl6405->config = ISL6405_ISEL1;
	isl6405->i2c = i2c;
	isl6405->i2c_addr = i2c_addr;
	fe->sec_priv = isl6405;

	/* bits which should be forced to '1' */
	isl6405->override_or = override_set;

	/* bits which should be forced to '0' */
	isl6405->override_and = ~override_clear;

	/* detect if it is present or not */
	if (isl6405_set_voltage(fe, SEC_VOLTAGE_OFF)) {
		kfree(isl6405);
		fe->sec_priv = NULL;
		return NULL;
	}

	/* install release callback */
	fe->ops.release_sec = isl6405_release;

	/* override frontend ops */
	fe->ops.set_voltage = isl6405_set_voltage;
	fe->ops.enable_high_lnb_voltage = isl6405_enable_high_lnb_voltage;

	return fe;
}