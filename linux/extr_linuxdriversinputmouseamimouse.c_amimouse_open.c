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
struct input_dev {int /*<<< orphan*/  dev; } ;
struct TYPE_2__ {unsigned short joy0dat; } ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_AMIGA_VERTB ; 
 TYPE_1__ amiga_custom ; 
 int /*<<< orphan*/  amimouse_interrupt ; 
 unsigned short amimouse_lastx ; 
 unsigned short amimouse_lasty ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int request_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,struct input_dev*) ; 

__attribute__((used)) static int amimouse_open(struct input_dev *dev)
{
	unsigned short joy0dat;
	int error;

	joy0dat = amiga_custom.joy0dat;

	amimouse_lastx = joy0dat & 0xff;
	amimouse_lasty = joy0dat >> 8;

	error = request_irq(IRQ_AMIGA_VERTB, amimouse_interrupt, 0, "amimouse",
			    dev);
	if (error)
		dev_err(&dev->dev, "Can't allocate irq %d\n", IRQ_AMIGA_VERTB);

	return error;
}