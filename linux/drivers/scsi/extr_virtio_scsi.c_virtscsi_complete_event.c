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
struct virtio_scsi_event_node {int /*<<< orphan*/  work; } ;
struct virtio_scsi {int /*<<< orphan*/  stop_events; } ;

/* Variables and functions */
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  system_freezable_wq ; 

__attribute__((used)) static void virtscsi_complete_event(struct virtio_scsi *vscsi, void *buf)
{
	struct virtio_scsi_event_node *event_node = buf;

	if (!vscsi->stop_events)
		queue_work(system_freezable_wq, &event_node->work);
}