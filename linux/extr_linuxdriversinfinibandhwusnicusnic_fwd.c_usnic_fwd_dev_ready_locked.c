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
struct usnic_fwd_dev {int /*<<< orphan*/  link_up; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int EPERM ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int usnic_fwd_dev_ready_locked(struct usnic_fwd_dev *ufdev)
{
	lockdep_assert_held(&ufdev->lock);

	if (!ufdev->link_up)
		return -EPERM;

	return 0;
}