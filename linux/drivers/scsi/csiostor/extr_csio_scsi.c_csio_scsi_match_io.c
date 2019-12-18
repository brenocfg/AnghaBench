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
typedef  int /*<<< orphan*/  uint64_t ;
struct scsi_cmnd {TYPE_1__* device; } ;
struct csio_scsi_level_data {int level; int /*<<< orphan*/  lnode; int /*<<< orphan*/  rnode; int /*<<< orphan*/  oslun; } ;
struct csio_ioreq {int /*<<< orphan*/  lnode; int /*<<< orphan*/  rnode; } ;
struct TYPE_2__ {int /*<<< orphan*/  lun; } ;

/* Variables and functions */
#define  CSIO_LEV_ALL 131 
#define  CSIO_LEV_LNODE 130 
#define  CSIO_LEV_LUN 129 
#define  CSIO_LEV_RNODE 128 
 struct scsi_cmnd* csio_scsi_cmnd (struct csio_ioreq*) ; 

__attribute__((used)) static bool
csio_scsi_match_io(struct csio_ioreq *ioreq, struct csio_scsi_level_data *sld)
{
	struct scsi_cmnd *scmnd = csio_scsi_cmnd(ioreq);

	switch (sld->level) {
	case CSIO_LEV_LUN:
		if (scmnd == NULL)
			return false;

		return ((ioreq->lnode == sld->lnode) &&
			(ioreq->rnode == sld->rnode) &&
			((uint64_t)scmnd->device->lun == sld->oslun));

	case CSIO_LEV_RNODE:
		return ((ioreq->lnode == sld->lnode) &&
				(ioreq->rnode == sld->rnode));
	case CSIO_LEV_LNODE:
		return (ioreq->lnode == sld->lnode);
	case CSIO_LEV_ALL:
		return true;
	default:
		return false;
	}
}