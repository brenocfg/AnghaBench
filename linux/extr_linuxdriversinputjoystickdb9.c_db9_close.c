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
struct parport {int dummy; } ;
struct input_dev {int dummy; } ;
struct db9 {int /*<<< orphan*/  mutex; TYPE_1__* pd; int /*<<< orphan*/  timer; int /*<<< orphan*/  used; } ;
struct TYPE_2__ {struct parport* port; } ;

/* Variables and functions */
 int /*<<< orphan*/  del_timer_sync (int /*<<< orphan*/ *) ; 
 struct db9* input_get_drvdata (struct input_dev*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  parport_data_forward (struct parport*) ; 
 int /*<<< orphan*/  parport_release (TYPE_1__*) ; 
 int /*<<< orphan*/  parport_write_control (struct parport*,int) ; 

__attribute__((used)) static void db9_close(struct input_dev *dev)
{
	struct db9 *db9 = input_get_drvdata(dev);
	struct parport *port = db9->pd->port;

	mutex_lock(&db9->mutex);
	if (!--db9->used) {
		del_timer_sync(&db9->timer);
		parport_write_control(port, 0x00);
		parport_data_forward(port);
		parport_release(db9->pd);
	}
	mutex_unlock(&db9->mutex);
}