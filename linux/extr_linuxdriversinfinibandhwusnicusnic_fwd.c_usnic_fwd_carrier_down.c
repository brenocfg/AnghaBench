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
struct usnic_fwd_dev {int /*<<< orphan*/  lock; scalar_t__ link_up; } ;

/* Variables and functions */
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

void usnic_fwd_carrier_down(struct usnic_fwd_dev *ufdev)
{
	spin_lock(&ufdev->lock);
	ufdev->link_up = 0;
	spin_unlock(&ufdev->lock);
}