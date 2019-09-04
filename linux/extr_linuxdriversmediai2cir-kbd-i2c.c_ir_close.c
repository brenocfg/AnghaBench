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
struct rc_dev {struct IR_i2c* priv; } ;
struct IR_i2c {int /*<<< orphan*/  work; } ;

/* Variables and functions */
 int /*<<< orphan*/  cancel_delayed_work_sync (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ir_close(struct rc_dev *dev)
{
	struct IR_i2c *ir = dev->priv;

	cancel_delayed_work_sync(&ir->work);
}