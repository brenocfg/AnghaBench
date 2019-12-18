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
struct virtio_balloon {int /*<<< orphan*/  report_free_page_work; int /*<<< orphan*/  balloon_wq; int /*<<< orphan*/  config_read_bitmap; int /*<<< orphan*/  vdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  VIRTIO_BALLOON_CONFIG_READ_CMD_ID ; 
 int /*<<< orphan*/  VIRTIO_BALLOON_F_FREE_PAGE_HINT ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ test_and_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  virtio_has_feature (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void virtio_balloon_queue_free_page_work(struct virtio_balloon *vb)
{
	if (!virtio_has_feature(vb->vdev, VIRTIO_BALLOON_F_FREE_PAGE_HINT))
		return;

	/* No need to queue the work if the bit was already set. */
	if (test_and_set_bit(VIRTIO_BALLOON_CONFIG_READ_CMD_ID,
			     &vb->config_read_bitmap))
		return;

	queue_work(vb->balloon_wq, &vb->report_free_page_work);
}