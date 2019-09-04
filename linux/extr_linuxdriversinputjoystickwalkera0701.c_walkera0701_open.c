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
struct walkera_dev {int /*<<< orphan*/  parport; int /*<<< orphan*/  pardevice; } ;
struct input_dev {int dummy; } ;

/* Variables and functions */
 int EBUSY ; 
 struct walkera_dev* input_get_drvdata (struct input_dev*) ; 
 scalar_t__ parport_claim (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  parport_enable_irq (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int walkera0701_open(struct input_dev *dev)
{
	struct walkera_dev *w = input_get_drvdata(dev);

	if (parport_claim(w->pardevice))
		return -EBUSY;

	parport_enable_irq(w->parport);
	return 0;
}