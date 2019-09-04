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
struct ddb_port {TYPE_1__* i2c; } ;
struct TYPE_2__ {int /*<<< orphan*/  adap; } ;

/* Variables and functions */
 scalar_t__ i2c_read (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int port_has_drxks(struct ddb_port *port)
{
	u8 val;

	if (i2c_read(&port->i2c->adap, 0x29, &val) < 0)
		return 0;
	if (i2c_read(&port->i2c->adap, 0x2a, &val) < 0)
		return 0;
	return 1;
}