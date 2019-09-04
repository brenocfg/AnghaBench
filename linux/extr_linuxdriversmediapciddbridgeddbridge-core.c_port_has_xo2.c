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
struct ddb_port {TYPE_1__* i2c; } ;
struct TYPE_2__ {int /*<<< orphan*/  adap; } ;

/* Variables and functions */
 scalar_t__ i2c_io (int /*<<< orphan*/ *,int,int*,int,int*,int) ; 

__attribute__((used)) static int port_has_xo2(struct ddb_port *port, u8 *type, u8 *id)
{
	u8 probe[1] = { 0x00 }, data[4];

	if (i2c_io(&port->i2c->adap, 0x10, probe, 1, data, 4))
		return 0;
	if (data[0] == 'D' && data[1] == 'F') {
		*id = data[2];
		*type = 1;
		return 1;
	}
	if (data[0] == 'C' && data[1] == 'I') {
		*id = data[2];
		*type = 2;
		return 1;
	}
	return 0;
}