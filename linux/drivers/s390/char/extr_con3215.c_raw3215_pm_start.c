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
struct raw3215_info {int /*<<< orphan*/  cdev; int /*<<< orphan*/  flags; int /*<<< orphan*/  port; } ;
struct ccw_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  RAW3215_FLUSHING ; 
 struct raw3215_info* dev_get_drvdata (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  get_ccwdev_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  raw3215_try_io (struct raw3215_info*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  tty_port_set_suspended (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int raw3215_pm_start(struct ccw_device *cdev)
{
	struct raw3215_info *raw;
	unsigned long flags;

	/* Allow I/O again and flush output buffer. */
	raw = dev_get_drvdata(&cdev->dev);
	spin_lock_irqsave(get_ccwdev_lock(raw->cdev), flags);
	tty_port_set_suspended(&raw->port, 0);
	raw->flags |= RAW3215_FLUSHING;
	raw3215_try_io(raw);
	raw->flags &= ~RAW3215_FLUSHING;
	spin_unlock_irqrestore(get_ccwdev_lock(raw->cdev), flags);
	return 0;
}