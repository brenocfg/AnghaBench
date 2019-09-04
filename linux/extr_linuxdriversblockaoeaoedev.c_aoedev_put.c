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
typedef  int /*<<< orphan*/  ulong ;
struct aoedev {int /*<<< orphan*/  ref; } ;

/* Variables and functions */
 int /*<<< orphan*/  devlist_lock ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void
aoedev_put(struct aoedev *d)
{
	ulong flags;

	spin_lock_irqsave(&devlist_lock, flags);
	d->ref--;
	spin_unlock_irqrestore(&devlist_lock, flags);
}