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
struct mddev {TYPE_1__* pers; struct md_cluster_info* cluster_info; } ;
struct md_cluster_info {int /*<<< orphan*/  suspend_lock; scalar_t__ suspend_lo; scalar_t__ suspend_hi; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* quiesce ) (struct mddev*,int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct mddev*,int) ; 
 int /*<<< orphan*/  stub2 (struct mddev*,int) ; 

__attribute__((used)) static void remove_suspend_info(struct mddev *mddev, int slot)
{
	struct md_cluster_info *cinfo = mddev->cluster_info;
	mddev->pers->quiesce(mddev, 1);
	spin_lock_irq(&cinfo->suspend_lock);
	cinfo->suspend_hi = 0;
	cinfo->suspend_lo = 0;
	spin_unlock_irq(&cinfo->suspend_lock);
	mddev->pers->quiesce(mddev, 0);
}