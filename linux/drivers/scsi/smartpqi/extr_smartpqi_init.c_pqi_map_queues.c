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
struct pqi_ctrl_info {int /*<<< orphan*/  pci_dev; } ;
struct TYPE_2__ {int /*<<< orphan*/ * map; } ;
struct Scsi_Host {TYPE_1__ tag_set; } ;

/* Variables and functions */
 size_t HCTX_TYPE_DEFAULT ; 
 int blk_mq_pci_map_queues (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct pqi_ctrl_info* shost_to_hba (struct Scsi_Host*) ; 

__attribute__((used)) static int pqi_map_queues(struct Scsi_Host *shost)
{
	struct pqi_ctrl_info *ctrl_info = shost_to_hba(shost);

	return blk_mq_pci_map_queues(&shost->tag_set.map[HCTX_TYPE_DEFAULT],
					ctrl_info->pci_dev, 0);
}