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
typedef  scalar_t__ u32 ;
struct vnic_dev {int notify_sz; int /*<<< orphan*/  notify_copy; int /*<<< orphan*/  notify; } ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int vnic_dev_notify_ready(struct vnic_dev *vdev)
{
	u32 *words;
	unsigned int nwords = vdev->notify_sz / 4;
	unsigned int i;
	u32 csum;

	if (!vdev->notify || !vdev->notify_sz)
		return 0;

	do {
		csum = 0;
		memcpy(&vdev->notify_copy, vdev->notify, vdev->notify_sz);
		words = (u32 *)&vdev->notify_copy;
		for (i = 1; i < nwords; i++)
			csum += words[i];
	} while (csum != words[0]);

	return 1;
}