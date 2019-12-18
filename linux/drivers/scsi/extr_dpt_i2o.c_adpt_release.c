#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct Scsi_Host {int dummy; } ;
struct TYPE_4__ {struct Scsi_Host* host; } ;
typedef  TYPE_1__ adpt_hba ;

/* Variables and functions */
 int /*<<< orphan*/  adpt_i2o_delete_hba (TYPE_1__*) ; 
 int /*<<< orphan*/  scsi_host_put (struct Scsi_Host*) ; 
 int /*<<< orphan*/  scsi_remove_host (struct Scsi_Host*) ; 

__attribute__((used)) static void adpt_release(adpt_hba *pHba)
{
	struct Scsi_Host *shost = pHba->host;

	scsi_remove_host(shost);
//	adpt_i2o_quiesce_hba(pHba);
	adpt_i2o_delete_hba(pHba);
	scsi_host_put(shost);
}