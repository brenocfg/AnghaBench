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
struct ec_i2c_device {int /*<<< orphan*/  adap; } ;

/* Variables and functions */
 int /*<<< orphan*/  i2c_del_adapter (int /*<<< orphan*/ *) ; 
 struct ec_i2c_device* platform_get_drvdata (struct platform_device*) ; 

__attribute__((used)) static int ec_i2c_remove(struct platform_device *dev)
{
	struct ec_i2c_device *bus = platform_get_drvdata(dev);

	i2c_del_adapter(&bus->adap);

	return 0;
}