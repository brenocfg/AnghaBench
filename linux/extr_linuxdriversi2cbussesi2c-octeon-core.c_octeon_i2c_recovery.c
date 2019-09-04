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
struct octeon_i2c {int /*<<< orphan*/  adap; } ;

/* Variables and functions */
 int i2c_recover_bus (int /*<<< orphan*/ *) ; 
 int octeon_i2c_init_lowlevel (struct octeon_i2c*) ; 

__attribute__((used)) static int octeon_i2c_recovery(struct octeon_i2c *i2c)
{
	int ret;

	ret = i2c_recover_bus(&i2c->adap);
	if (ret)
		/* recover failed, try hardware re-init */
		ret = octeon_i2c_init_lowlevel(i2c);
	return ret;
}