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
struct serio_driver {int dummy; } ;
struct serio {int /*<<< orphan*/  dev; } ;
struct TYPE_2__ {int /*<<< orphan*/ * xport_ops; } ;
struct iforce_serio {TYPE_1__ iforce; struct serio* serio; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUS_RS232 ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int iforce_init_device (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  iforce_serio_xport_ops ; 
 int /*<<< orphan*/  kfree (struct iforce_serio*) ; 
 struct iforce_serio* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  serio_close (struct serio*) ; 
 int serio_open (struct serio*,struct serio_driver*) ; 
 int /*<<< orphan*/  serio_set_drvdata (struct serio*,struct iforce_serio*) ; 

__attribute__((used)) static int iforce_serio_connect(struct serio *serio, struct serio_driver *drv)
{
	struct iforce_serio *iforce_serio;
	int err;

	iforce_serio = kzalloc(sizeof(*iforce_serio), GFP_KERNEL);
	if (!iforce_serio)
		return -ENOMEM;

	iforce_serio->iforce.xport_ops = &iforce_serio_xport_ops;

	iforce_serio->serio = serio;
	serio_set_drvdata(serio, iforce_serio);

	err = serio_open(serio, drv);
	if (err)
		goto fail1;

	err = iforce_init_device(&serio->dev, BUS_RS232, &iforce_serio->iforce);
	if (err)
		goto fail2;

	return 0;

 fail2:	serio_close(serio);
 fail1:	serio_set_drvdata(serio, NULL);
	kfree(iforce_serio);
	return err;
}