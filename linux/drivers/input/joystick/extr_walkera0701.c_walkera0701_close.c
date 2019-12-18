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
struct walkera_dev {int /*<<< orphan*/  pardevice; int /*<<< orphan*/  timer; int /*<<< orphan*/  parport; } ;
struct input_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  hrtimer_cancel (int /*<<< orphan*/ *) ; 
 struct walkera_dev* input_get_drvdata (struct input_dev*) ; 
 int /*<<< orphan*/  parport_disable_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  parport_release (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void walkera0701_close(struct input_dev *dev)
{
	struct walkera_dev *w = input_get_drvdata(dev);

	parport_disable_irq(w->parport);
	hrtimer_cancel(&w->timer);

	parport_release(w->pardevice);
}