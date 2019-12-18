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
typedef  int /*<<< orphan*/  u32 ;
struct isci_remote_device {scalar_t__ started_request_count; } ;
struct isci_host {int /*<<< orphan*/  scic_lock; } ;

/* Variables and functions */
 scalar_t__ isci_compare_suspendcount (struct isci_remote_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static bool isci_check_devempty(
	struct isci_host *ihost,
	struct isci_remote_device *idev,
	u32 localcount)
{
	unsigned long flags;
	bool res;

	spin_lock_irqsave(&ihost->scic_lock, flags);
	res = isci_compare_suspendcount(idev, localcount)
		&& idev->started_request_count == 0;
	spin_unlock_irqrestore(&ihost->scic_lock, flags);

	return res;
}