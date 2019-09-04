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
struct msgdma_device {int /*<<< orphan*/  done_list; int /*<<< orphan*/  pending_list; int /*<<< orphan*/  active_list; } ;

/* Variables and functions */
 int /*<<< orphan*/  msgdma_free_desc_list (struct msgdma_device*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void msgdma_free_descriptors(struct msgdma_device *mdev)
{
	msgdma_free_desc_list(mdev, &mdev->active_list);
	msgdma_free_desc_list(mdev, &mdev->pending_list);
	msgdma_free_desc_list(mdev, &mdev->done_list);
}