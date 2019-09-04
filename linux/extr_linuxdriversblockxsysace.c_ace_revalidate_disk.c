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
struct gendisk {struct ace_device* private_data; } ;
struct ace_device {int id_result; int /*<<< orphan*/  dev; int /*<<< orphan*/  id_completion; int /*<<< orphan*/  fsm_tasklet; int /*<<< orphan*/  lock; int /*<<< orphan*/  id_req_count; scalar_t__ media_change; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  tasklet_schedule (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wait_for_completion (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ace_revalidate_disk(struct gendisk *gd)
{
	struct ace_device *ace = gd->private_data;
	unsigned long flags;

	dev_dbg(ace->dev, "ace_revalidate_disk()\n");

	if (ace->media_change) {
		dev_dbg(ace->dev, "requesting cf id and scheduling tasklet\n");

		spin_lock_irqsave(&ace->lock, flags);
		ace->id_req_count++;
		spin_unlock_irqrestore(&ace->lock, flags);

		tasklet_schedule(&ace->fsm_tasklet);
		wait_for_completion(&ace->id_completion);
	}

	dev_dbg(ace->dev, "revalidate complete\n");
	return ace->id_result;
}