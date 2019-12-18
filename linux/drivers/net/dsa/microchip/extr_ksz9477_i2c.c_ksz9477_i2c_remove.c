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
struct ksz_device {int dummy; } ;
struct i2c_client {int dummy; } ;

/* Variables and functions */
 struct ksz_device* i2c_get_clientdata (struct i2c_client*) ; 
 int /*<<< orphan*/  ksz_switch_remove (struct ksz_device*) ; 

__attribute__((used)) static int ksz9477_i2c_remove(struct i2c_client *i2c)
{
	struct ksz_device *dev = i2c_get_clientdata(i2c);

	ksz_switch_remove(dev);

	return 0;
}