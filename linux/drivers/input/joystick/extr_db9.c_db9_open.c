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
struct parport {int dummy; } ;
struct input_dev {int dummy; } ;
struct db9 {size_t mode; int /*<<< orphan*/  mutex; int /*<<< orphan*/  timer; TYPE_1__* pd; int /*<<< orphan*/  used; } ;
struct TYPE_4__ {scalar_t__ reverse; } ;
struct TYPE_3__ {struct parport* port; } ;

/* Variables and functions */
 int /*<<< orphan*/  DB9_NORMAL ; 
 scalar_t__ DB9_REFRESH_TIME ; 
 TYPE_2__* db9_modes ; 
 struct db9* input_get_drvdata (struct input_dev*) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 int mutex_lock_interruptible (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  parport_claim (TYPE_1__*) ; 
 int /*<<< orphan*/  parport_data_reverse (struct parport*) ; 
 int /*<<< orphan*/  parport_write_control (struct parport*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  parport_write_data (struct parport*,int) ; 

__attribute__((used)) static int db9_open(struct input_dev *dev)
{
	struct db9 *db9 = input_get_drvdata(dev);
	struct parport *port = db9->pd->port;
	int err;

	err = mutex_lock_interruptible(&db9->mutex);
	if (err)
		return err;

	if (!db9->used++) {
		parport_claim(db9->pd);
		parport_write_data(port, 0xff);
		if (db9_modes[db9->mode].reverse) {
			parport_data_reverse(port);
			parport_write_control(port, DB9_NORMAL);
		}
		mod_timer(&db9->timer, jiffies + DB9_REFRESH_TIME);
	}

	mutex_unlock(&db9->mutex);
	return 0;
}