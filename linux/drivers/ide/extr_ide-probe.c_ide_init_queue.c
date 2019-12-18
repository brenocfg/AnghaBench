#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct request_queue {TYPE_2__* queuedata; } ;
struct ide_request {int dummy; } ;
struct blk_mq_tag_set {int nr_hw_queues; int queue_depth; int reserved_tags; int cmd_size; int flags; int /*<<< orphan*/  numa_node; int /*<<< orphan*/ * ops; } ;
struct TYPE_5__ {int rqsize; } ;
typedef  TYPE_1__ ide_hwif_t ;
struct TYPE_6__ {struct request_queue* queue; struct blk_mq_tag_set tag_set; TYPE_1__* hwif; } ;
typedef  TYPE_2__ ide_drive_t ;

/* Variables and functions */
 int BLK_MQ_F_BLOCKING ; 
 int BLK_MQ_F_SHOULD_MERGE ; 
 scalar_t__ IS_ERR (struct request_queue*) ; 
 int PRD_ENTRIES ; 
 int /*<<< orphan*/  QUEUE_FLAG_SCSI_PASSTHROUGH ; 
 scalar_t__ blk_mq_alloc_tag_set (struct blk_mq_tag_set*) ; 
 int /*<<< orphan*/  blk_mq_free_tag_set (struct blk_mq_tag_set*) ; 
 struct request_queue* blk_mq_init_queue (struct blk_mq_tag_set*) ; 
 int /*<<< orphan*/  blk_queue_flag_set (int /*<<< orphan*/ ,struct request_queue*) ; 
 int /*<<< orphan*/  blk_queue_max_hw_sectors (struct request_queue*,int) ; 
 int /*<<< orphan*/  blk_queue_max_segments (struct request_queue*,int) ; 
 int /*<<< orphan*/  blk_queue_segment_boundary (struct request_queue*,int) ; 
 int /*<<< orphan*/  hwif_to_node (TYPE_1__*) ; 
 int /*<<< orphan*/  ide_mq_ops ; 

__attribute__((used)) static int ide_init_queue(ide_drive_t *drive)
{
	struct request_queue *q;
	ide_hwif_t *hwif = drive->hwif;
	int max_sectors = 256;
	int max_sg_entries = PRD_ENTRIES;
	struct blk_mq_tag_set *set;

	/*
	 *	Our default set up assumes the normal IDE case,
	 *	that is 64K segmenting, standard PRD setup
	 *	and LBA28. Some drivers then impose their own
	 *	limits and LBA48 we could raise it but as yet
	 *	do not.
	 */

	set = &drive->tag_set;
	set->ops = &ide_mq_ops;
	set->nr_hw_queues = 1;
	set->queue_depth = 32;
	set->reserved_tags = 1;
	set->cmd_size = sizeof(struct ide_request);
	set->numa_node = hwif_to_node(hwif);
	set->flags = BLK_MQ_F_SHOULD_MERGE | BLK_MQ_F_BLOCKING;
	if (blk_mq_alloc_tag_set(set))
		return 1;

	q = blk_mq_init_queue(set);
	if (IS_ERR(q)) {
		blk_mq_free_tag_set(set);
		return 1;
	}

	blk_queue_flag_set(QUEUE_FLAG_SCSI_PASSTHROUGH, q);

	q->queuedata = drive;
	blk_queue_segment_boundary(q, 0xffff);

	if (hwif->rqsize < max_sectors)
		max_sectors = hwif->rqsize;
	blk_queue_max_hw_sectors(q, max_sectors);

#ifdef CONFIG_PCI
	/* When we have an IOMMU, we may have a problem where pci_map_sg()
	 * creates segments that don't completely match our boundary
	 * requirements and thus need to be broken up again. Because it
	 * doesn't align properly either, we may actually have to break up
	 * to more segments than what was we got in the first place, a max
	 * worst case is twice as many.
	 * This will be fixed once we teach pci_map_sg() about our boundary
	 * requirements, hopefully soon. *FIXME*
	 */
	max_sg_entries >>= 1;
#endif /* CONFIG_PCI */

	blk_queue_max_segments(q, max_sg_entries);

	/* assign drive queue */
	drive->queue = q;

	return 0;
}