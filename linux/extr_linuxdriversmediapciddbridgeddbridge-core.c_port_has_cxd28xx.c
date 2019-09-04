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
typedef  int /*<<< orphan*/  u8 ;
struct i2c_adapter {int dummy; } ;
struct ddb_port {TYPE_1__* i2c; } ;
struct TYPE_2__ {struct i2c_adapter adap; } ;

/* Variables and functions */
 int i2c_read_reg (struct i2c_adapter*,int,int,int /*<<< orphan*/ *) ; 
 int i2c_write_reg (struct i2c_adapter*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int port_has_cxd28xx(struct ddb_port *port, u8 *id)
{
	struct i2c_adapter *i2c = &port->i2c->adap;
	int status;

	status = i2c_write_reg(&port->i2c->adap, 0x6e, 0, 0);
	if (status)
		return 0;
	status = i2c_read_reg(i2c, 0x6e, 0xfd, id);
	if (status)
		return 0;
	return 1;
}