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
struct video_device {int /*<<< orphan*/  fh_lock; int /*<<< orphan*/  fh_list; } ;

/* Variables and functions */
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static bool vivid_is_in_use(struct video_device *vdev)
{
	unsigned long flags;
	bool res;

	spin_lock_irqsave(&vdev->fh_lock, flags);
	res = !list_empty(&vdev->fh_list);
	spin_unlock_irqrestore(&vdev->fh_lock, flags);
	return res;
}