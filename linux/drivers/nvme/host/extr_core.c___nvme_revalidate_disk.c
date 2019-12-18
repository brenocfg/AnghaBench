#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct t10_pi_tuple {int dummy; } ;
struct nvme_ns {int lba_shift; int ms; int ext; int pi_type; TYPE_2__* head; int /*<<< orphan*/  queue; void* noiob; } ;
struct nvme_id_ns {size_t flbas; int dps; TYPE_1__* lbaf; int /*<<< orphan*/  noiob; } ;
struct gendisk {int /*<<< orphan*/  queue; struct nvme_ns* private_data; } ;
struct TYPE_4__ {struct gendisk* disk; } ;
struct TYPE_3__ {int ds; int /*<<< orphan*/  ms; } ;

/* Variables and functions */
 int NVME_NS_DPS_PI_MASK ; 
 size_t NVME_NS_FLBAS_LBA_MASK ; 
 int NVME_NS_FLBAS_META_EXT ; 
 int /*<<< orphan*/  blk_queue_stack_limits (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nvme_set_chunk_size (struct nvme_ns*) ; 
 int /*<<< orphan*/  nvme_update_disk_info (struct gendisk*,struct nvme_ns*,struct nvme_id_ns*) ; 
 int /*<<< orphan*/  revalidate_disk (struct gendisk*) ; 

__attribute__((used)) static void __nvme_revalidate_disk(struct gendisk *disk, struct nvme_id_ns *id)
{
	struct nvme_ns *ns = disk->private_data;

	/*
	 * If identify namespace failed, use default 512 byte block size so
	 * block layer can use before failing read/write for 0 capacity.
	 */
	ns->lba_shift = id->lbaf[id->flbas & NVME_NS_FLBAS_LBA_MASK].ds;
	if (ns->lba_shift == 0)
		ns->lba_shift = 9;
	ns->noiob = le16_to_cpu(id->noiob);
	ns->ms = le16_to_cpu(id->lbaf[id->flbas & NVME_NS_FLBAS_LBA_MASK].ms);
	ns->ext = ns->ms && (id->flbas & NVME_NS_FLBAS_META_EXT);
	/* the PI implementation requires metadata equal t10 pi tuple size */
	if (ns->ms == sizeof(struct t10_pi_tuple))
		ns->pi_type = id->dps & NVME_NS_DPS_PI_MASK;
	else
		ns->pi_type = 0;

	if (ns->noiob)
		nvme_set_chunk_size(ns);
	nvme_update_disk_info(disk, ns, id);
#ifdef CONFIG_NVME_MULTIPATH
	if (ns->head->disk) {
		nvme_update_disk_info(ns->head->disk, ns, id);
		blk_queue_stack_limits(ns->head->disk->queue, ns->queue);
		revalidate_disk(ns->head->disk);
	}
#endif
}