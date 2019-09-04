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
struct tgfx {int /*<<< orphan*/  sem; int /*<<< orphan*/  timer; TYPE_1__* pd; int /*<<< orphan*/  used; } ;
struct input_dev {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  port; } ;

/* Variables and functions */
 scalar_t__ TGFX_REFRESH_TIME ; 
 struct tgfx* input_get_drvdata (struct input_dev*) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 int mutex_lock_interruptible (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  parport_claim (TYPE_1__*) ; 
 int /*<<< orphan*/  parport_write_control (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int tgfx_open(struct input_dev *dev)
{
	struct tgfx *tgfx = input_get_drvdata(dev);
	int err;

	err = mutex_lock_interruptible(&tgfx->sem);
	if (err)
		return err;

	if (!tgfx->used++) {
		parport_claim(tgfx->pd);
		parport_write_control(tgfx->pd->port, 0x04);
		mod_timer(&tgfx->timer, jiffies + TGFX_REFRESH_TIME);
	}

	mutex_unlock(&tgfx->sem);
	return 0;
}