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
typedef  int /*<<< orphan*/  u8 ;
struct scsi_device {scalar_t__ type; int allow_restart; scalar_t__ tagged_supported; int /*<<< orphan*/  request_queue; scalar_t__ lun; int /*<<< orphan*/  id; int /*<<< orphan*/  channel; TYPE_1__* host; struct pmcraid_resource_entry* hostdata; } ;
struct pmcraid_resource_entry {int /*<<< orphan*/  cfg_entry; } ;
struct TYPE_2__ {int /*<<< orphan*/  unique_id; } ;

/* Variables and functions */
 int ENXIO ; 
 int /*<<< orphan*/  PMCRAID_VSET_IO_TIMEOUT ; 
 int /*<<< orphan*/  PMCRAID_VSET_MAX_SECTORS ; 
 scalar_t__ RES_IS_GSCSI (int /*<<< orphan*/ ) ; 
 scalar_t__ RES_IS_VSET (int /*<<< orphan*/ ) ; 
 scalar_t__ TYPE_ENCLOSURE ; 
 int /*<<< orphan*/  blk_queue_max_hw_sectors (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  blk_queue_rq_timeout (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pmcraid_info (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int pmcraid_slave_configure(struct scsi_device *scsi_dev)
{
	struct pmcraid_resource_entry *res = scsi_dev->hostdata;

	if (!res)
		return 0;

	/* LLD exposes VSETs and Enclosure devices only */
	if (RES_IS_GSCSI(res->cfg_entry) &&
	    scsi_dev->type != TYPE_ENCLOSURE)
		return -ENXIO;

	pmcraid_info("configuring %x:%x:%x:%x\n",
		     scsi_dev->host->unique_id,
		     scsi_dev->channel,
		     scsi_dev->id,
		     (u8)scsi_dev->lun);

	if (RES_IS_GSCSI(res->cfg_entry)) {
		scsi_dev->allow_restart = 1;
	} else if (RES_IS_VSET(res->cfg_entry)) {
		scsi_dev->allow_restart = 1;
		blk_queue_rq_timeout(scsi_dev->request_queue,
				     PMCRAID_VSET_IO_TIMEOUT);
		blk_queue_max_hw_sectors(scsi_dev->request_queue,
				      PMCRAID_VSET_MAX_SECTORS);
	}

	/*
	 * We never want to report TCQ support for these types of devices.
	 */
	if (!RES_IS_GSCSI(res->cfg_entry) && !RES_IS_VSET(res->cfg_entry))
		scsi_dev->tagged_supported = 0;

	return 0;
}