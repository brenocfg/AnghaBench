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
struct scsi_driver {int /*<<< orphan*/  (* eh_reset ) (struct scsi_cmnd*) ;} ;
struct scsi_cmnd {int /*<<< orphan*/  request; } ;

/* Variables and functions */
 int /*<<< orphan*/  blk_rq_is_passthrough (int /*<<< orphan*/ ) ; 
 struct scsi_driver* scsi_cmd_to_driver (struct scsi_cmnd*) ; 
 int /*<<< orphan*/  stub1 (struct scsi_cmnd*) ; 

__attribute__((used)) static void scsi_eh_reset(struct scsi_cmnd *scmd)
{
	if (!blk_rq_is_passthrough(scmd->request)) {
		struct scsi_driver *sdrv = scsi_cmd_to_driver(scmd);
		if (sdrv->eh_reset)
			sdrv->eh_reset(scmd);
	}
}