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
struct ksz_device {TYPE_1__* dev_ops; } ;
struct i2c_client {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* shutdown ) (struct ksz_device*) ;} ;

/* Variables and functions */
 struct ksz_device* i2c_get_clientdata (struct i2c_client*) ; 
 int /*<<< orphan*/  stub1 (struct ksz_device*) ; 

__attribute__((used)) static void ksz9477_i2c_shutdown(struct i2c_client *i2c)
{
	struct ksz_device *dev = i2c_get_clientdata(i2c);

	if (dev && dev->dev_ops->shutdown)
		dev->dev_ops->shutdown(dev);
}