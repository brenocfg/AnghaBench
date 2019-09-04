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
struct ngene_channel {int number; TYPE_2__* dev; } ;
struct i2c_adapter {int dummy; } ;
struct TYPE_4__ {TYPE_1__* channel; } ;
struct TYPE_3__ {struct i2c_adapter i2c_adapter; } ;

/* Variables and functions */

__attribute__((used)) static struct i2c_adapter *i2c_adapter_from_chan(struct ngene_channel *chan)
{
	/* tuner 1+2: i2c adapter #0, tuner 3+4: i2c adapter #1 */
	if (chan->number < 2)
		return &chan->dev->channel[0].i2c_adapter;

	return &chan->dev->channel[1].i2c_adapter;
}