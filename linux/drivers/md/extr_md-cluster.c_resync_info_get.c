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
struct mddev {struct md_cluster_info* cluster_info; } ;
struct md_cluster_info {int /*<<< orphan*/  suspend_lock; int /*<<< orphan*/  suspend_hi; int /*<<< orphan*/  suspend_lo; } ;
typedef  int /*<<< orphan*/  sector_t ;

/* Variables and functions */
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void resync_info_get(struct mddev *mddev, sector_t *lo, sector_t *hi)
{
	struct md_cluster_info *cinfo = mddev->cluster_info;

	spin_lock_irq(&cinfo->suspend_lock);
	*lo = cinfo->suspend_lo;
	*hi = cinfo->suspend_hi;
	spin_unlock_irq(&cinfo->suspend_lock);
}