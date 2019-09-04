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
struct platform_device {int dummy; } ;
struct i2c_versatile {int /*<<< orphan*/  adap; } ;

/* Variables and functions */
 int /*<<< orphan*/  i2c_del_adapter (int /*<<< orphan*/ *) ; 
 struct i2c_versatile* platform_get_drvdata (struct platform_device*) ; 

__attribute__((used)) static int i2c_versatile_remove(struct platform_device *dev)
{
	struct i2c_versatile *i2c = platform_get_drvdata(dev);

	i2c_del_adapter(&i2c->adap);
	return 0;
}