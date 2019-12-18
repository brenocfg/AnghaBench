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
struct scsi_cmnd {TYPE_1__* device; } ;
struct myrs_hba {int /*<<< orphan*/  io_base; int /*<<< orphan*/  (* reset ) (int /*<<< orphan*/ ) ;} ;
struct Scsi_Host {int dummy; } ;
struct TYPE_2__ {struct Scsi_Host* host; } ;

/* Variables and functions */
 int SUCCESS ; 
 struct myrs_hba* shost_priv (struct Scsi_Host*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 

int myrs_host_reset(struct scsi_cmnd *scmd)
{
	struct Scsi_Host *shost = scmd->device->host;
	struct myrs_hba *cs = shost_priv(shost);

	cs->reset(cs->io_base);
	return SUCCESS;
}