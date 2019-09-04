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
struct w8001 {int /*<<< orphan*/  id; int /*<<< orphan*/  phys; } ;
struct serio {int /*<<< orphan*/  dev; } ;
struct TYPE_3__ {int /*<<< orphan*/ * parent; } ;
struct TYPE_4__ {int vendor; int version; int /*<<< orphan*/  product; int /*<<< orphan*/  bustype; } ;
struct input_dev {TYPE_1__ dev; int /*<<< orphan*/  close; int /*<<< orphan*/  open; TYPE_2__ id; int /*<<< orphan*/  phys; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUS_RS232 ; 
 int /*<<< orphan*/  input_set_drvdata (struct input_dev*,struct w8001*) ; 
 int /*<<< orphan*/  w8001_close ; 
 int /*<<< orphan*/  w8001_open ; 

__attribute__((used)) static void w8001_set_devdata(struct input_dev *dev, struct w8001 *w8001,
			      struct serio *serio)
{
	dev->phys = w8001->phys;
	dev->id.bustype = BUS_RS232;
	dev->id.product = w8001->id;
	dev->id.vendor = 0x056a;
	dev->id.version = 0x0100;
	dev->open = w8001_open;
	dev->close = w8001_close;

	dev->dev.parent = &serio->dev;

	input_set_drvdata(dev, w8001);
}