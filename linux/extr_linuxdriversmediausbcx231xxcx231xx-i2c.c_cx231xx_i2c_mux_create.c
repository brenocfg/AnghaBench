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
struct cx231xx {TYPE_2__* muxc; int /*<<< orphan*/  dev; TYPE_1__* i2c_bus; } ;
struct TYPE_4__ {struct cx231xx* priv; } ;
struct TYPE_3__ {int /*<<< orphan*/  i2c_adap; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  cx231xx_i2c_mux_select ; 
 TYPE_2__* i2c_mux_alloc (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int cx231xx_i2c_mux_create(struct cx231xx *dev)
{
	dev->muxc = i2c_mux_alloc(&dev->i2c_bus[1].i2c_adap, dev->dev, 2, 0, 0,
				  cx231xx_i2c_mux_select, NULL);
	if (!dev->muxc)
		return -ENOMEM;
	dev->muxc->priv = dev;
	return 0;
}