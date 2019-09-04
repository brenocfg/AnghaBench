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
typedef  size_t u32 ;
struct ddb_port {scalar_t__ lnr; scalar_t__ nr; TYPE_1__* i2c; struct ddb* dev; } ;
struct ddb {size_t i2c_num; TYPE_1__* i2c; } ;
struct TYPE_2__ {scalar_t__ link; scalar_t__ nr; } ;

/* Variables and functions */

__attribute__((used)) static int ddb_port_match_i2c(struct ddb_port *port)
{
	struct ddb *dev = port->dev;
	u32 i;

	for (i = 0; i < dev->i2c_num; i++) {
		if (dev->i2c[i].link == port->lnr &&
		    dev->i2c[i].nr == port->nr) {
			port->i2c = &dev->i2c[i];
			return 1;
		}
	}
	return 0;
}