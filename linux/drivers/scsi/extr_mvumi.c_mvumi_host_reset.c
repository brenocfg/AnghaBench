#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct scsi_cmnd {int /*<<< orphan*/  retries; int /*<<< orphan*/ * cmnd; TYPE_3__* request; TYPE_2__* device; } ;
struct mvumi_hba {TYPE_4__* instancet; } ;
struct TYPE_8__ {int (* reset_host ) (struct mvumi_hba*) ;} ;
struct TYPE_7__ {int /*<<< orphan*/  tag; } ;
struct TYPE_6__ {TYPE_1__* host; } ;
struct TYPE_5__ {scalar_t__ hostdata; } ;

/* Variables and functions */
 int /*<<< orphan*/  KERN_NOTICE ; 
 int /*<<< orphan*/  scmd_printk (int /*<<< orphan*/ ,struct scsi_cmnd*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int stub1 (struct mvumi_hba*) ; 

__attribute__((used)) static int mvumi_host_reset(struct scsi_cmnd *scmd)
{
	struct mvumi_hba *mhba;

	mhba = (struct mvumi_hba *) scmd->device->host->hostdata;

	scmd_printk(KERN_NOTICE, scmd, "RESET -%u cmd=%x retries=%x\n",
			scmd->request->tag, scmd->cmnd[0], scmd->retries);

	return mhba->instancet->reset_host(mhba);
}