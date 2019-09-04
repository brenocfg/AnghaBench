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
struct ddb_i2c {int /*<<< orphan*/  adap; } ;
struct ddb {int i2c_num; struct ddb_i2c* i2c; } ;

/* Variables and functions */
 int /*<<< orphan*/  i2c_del_adapter (int /*<<< orphan*/ *) ; 

void ddb_i2c_release(struct ddb *dev)
{
	int i;
	struct ddb_i2c *i2c;

	for (i = 0; i < dev->i2c_num; i++) {
		i2c = &dev->i2c[i];
		i2c_del_adapter(&i2c->adap);
	}
}