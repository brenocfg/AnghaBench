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
typedef  int /*<<< orphan*/  u64 ;
struct usnic_fwd_dev {int /*<<< orphan*/  lock; } ;
typedef  enum vnic_devcmd_cmd { ____Placeholder_vnic_devcmd_cmd } vnic_devcmd_cmd ;

/* Variables and functions */
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int usnic_fwd_devcmd_locked (struct usnic_fwd_dev*,int,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int usnic_fwd_devcmd(struct usnic_fwd_dev *ufdev, int vnic_idx,
				enum vnic_devcmd_cmd cmd, u64 *a0, u64 *a1)
{
	int status;

	spin_lock(&ufdev->lock);
	status = usnic_fwd_devcmd_locked(ufdev, vnic_idx, cmd, a0, a1);
	spin_unlock(&ufdev->lock);

	return status;
}