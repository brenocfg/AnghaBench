#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct i2c_adapter {int dummy; } ;
struct dvb_ca_en50221 {struct ddb_ci* data; } ;
struct ddb_ci {TYPE_2__* port; } ;
struct TYPE_4__ {scalar_t__ type; TYPE_1__* i2c; } ;
struct TYPE_3__ {struct i2c_adapter adap; } ;

/* Variables and functions */
 scalar_t__ DDB_CI_EXTERNAL_XO2 ; 
 int i2c_write_reg (struct i2c_adapter*,int,int,int) ; 

__attribute__((used)) static int write_cam_control_xo2(struct dvb_ca_en50221 *ca, int slot,
				 u8 address, u8 value)
{
	struct ddb_ci *ci = ca->data;
	struct i2c_adapter *i2c = &ci->port->i2c->adap;
	u8 adr = (ci->port->type == DDB_CI_EXTERNAL_XO2) ? 0x12 : 0x13;

	return i2c_write_reg(i2c, adr, 0x20 | (address & 3), value);
}