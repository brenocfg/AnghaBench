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
struct ts2020_priv {int /*<<< orphan*/  regmap_mutex; TYPE_2__* fe; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* i2c_gate_ctrl ) (TYPE_2__*,int /*<<< orphan*/ ) ;} ;
struct TYPE_4__ {TYPE_1__ ops; } ;

/* Variables and functions */
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ts2020_regmap_unlock(void *__dev)
{
	struct ts2020_priv *dev = __dev;

	if (dev->fe->ops.i2c_gate_ctrl)
		dev->fe->ops.i2c_gate_ctrl(dev->fe, 0);
	mutex_unlock(&dev->regmap_mutex);
}