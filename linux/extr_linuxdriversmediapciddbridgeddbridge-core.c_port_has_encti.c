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
typedef  int /*<<< orphan*/  u8 ;
struct device {int dummy; } ;
struct ddb_port {TYPE_2__* i2c; TYPE_1__* dev; } ;
struct TYPE_4__ {int /*<<< orphan*/  adap; } ;
struct TYPE_3__ {struct device* dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_info (struct device*,char*,int /*<<< orphan*/ ) ; 
 int i2c_read_reg (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int port_has_encti(struct ddb_port *port)
{
	struct device *dev = port->dev->dev;
	u8 val;
	int ret = i2c_read_reg(&port->i2c->adap, 0x20, 0, &val);

	if (!ret)
		dev_info(dev, "[0x20]=0x%02x\n", val);
	return ret ? 0 : 1;
}