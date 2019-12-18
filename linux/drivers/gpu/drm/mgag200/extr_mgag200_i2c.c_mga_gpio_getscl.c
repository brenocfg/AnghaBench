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
struct mga_i2c_chan {int clock; TYPE_1__* dev; } ;
struct mga_device {int dummy; } ;
struct TYPE_2__ {struct mga_device* dev_private; } ;

/* Variables and functions */
 int mga_i2c_read_gpio (struct mga_device*) ; 

__attribute__((used)) static int mga_gpio_getscl(void *data)
{
	struct mga_i2c_chan *i2c = data;
	struct mga_device *mdev = i2c->dev->dev_private;
	return (mga_i2c_read_gpio(mdev) & i2c->clock) ? 1 : 0;
}