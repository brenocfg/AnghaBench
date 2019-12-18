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
struct virtio_scsi {int num_queues; int /*<<< orphan*/ * req_vqs; } ;

/* Variables and functions */
 int /*<<< orphan*/  virtscsi_complete_cmd ; 
 int /*<<< orphan*/  virtscsi_vq_done (struct virtio_scsi*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void virtscsi_poll_requests(struct virtio_scsi *vscsi)
{
	int i, num_vqs;

	num_vqs = vscsi->num_queues;
	for (i = 0; i < num_vqs; i++)
		virtscsi_vq_done(vscsi, &vscsi->req_vqs[i],
				 virtscsi_complete_cmd);
}