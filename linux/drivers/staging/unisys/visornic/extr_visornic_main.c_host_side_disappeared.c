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
struct visornic_devdata {int /*<<< orphan*/  priv_lock; int /*<<< orphan*/ * dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void host_side_disappeared(struct visornic_devdata *devdata)
{
	unsigned long flags;

	spin_lock_irqsave(&devdata->priv_lock, flags);
	/* indicate device destroyed */
	devdata->dev = NULL;
	spin_unlock_irqrestore(&devdata->priv_lock, flags);
}