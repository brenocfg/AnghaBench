#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {TYPE_4__* frontend; } ;
struct au0828_dev {TYPE_3__ dvb; } ;
struct TYPE_5__ {int /*<<< orphan*/  (* i2c_gate_ctrl ) (TYPE_4__*,int) ;} ;
struct TYPE_6__ {TYPE_1__ analog_ops; } ;
struct TYPE_8__ {TYPE_2__ ops; } ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (TYPE_4__*,int) ; 

__attribute__((used)) static inline void i2c_gate_ctrl(struct au0828_dev *dev, int val)
{
	if (dev->dvb.frontend && dev->dvb.frontend->ops.analog_ops.i2c_gate_ctrl)
		dev->dvb.frontend->ops.analog_ops.i2c_gate_ctrl(dev->dvb.frontend, val);
}