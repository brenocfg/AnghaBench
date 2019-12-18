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
struct list_head {int dummy; } ;
struct fdp1_job {int /*<<< orphan*/  list; } ;
struct fdp1_dev {int /*<<< orphan*/  irqlock; } ;

/* Variables and functions */
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,struct list_head*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void list_add_job(struct fdp1_dev *fdp1,
			 struct list_head *list,
			 struct fdp1_job *job)
{
	unsigned long flags;

	spin_lock_irqsave(&fdp1->irqlock, flags);
	list_add_tail(&job->list, list);
	spin_unlock_irqrestore(&fdp1->irqlock, flags);
}