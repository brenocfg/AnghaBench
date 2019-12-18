#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct virtio_scsi {int /*<<< orphan*/  vdev; } ;
struct blk_mq_queue_map {int dummy; } ;
struct TYPE_2__ {struct blk_mq_queue_map* map; } ;
struct Scsi_Host {TYPE_1__ tag_set; } ;

/* Variables and functions */
 size_t HCTX_TYPE_DEFAULT ; 
 int blk_mq_virtio_map_queues (struct blk_mq_queue_map*,int /*<<< orphan*/ ,int) ; 
 struct virtio_scsi* shost_priv (struct Scsi_Host*) ; 

__attribute__((used)) static int virtscsi_map_queues(struct Scsi_Host *shost)
{
	struct virtio_scsi *vscsi = shost_priv(shost);
	struct blk_mq_queue_map *qmap = &shost->tag_set.map[HCTX_TYPE_DEFAULT];

	return blk_mq_virtio_map_queues(qmap, vscsi->vdev, 2);
}