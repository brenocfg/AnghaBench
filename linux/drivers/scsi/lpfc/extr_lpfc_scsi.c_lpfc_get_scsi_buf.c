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
struct scsi_cmnd {int dummy; } ;
struct lpfc_nodelist {int dummy; } ;
struct lpfc_io_buf {int dummy; } ;
struct lpfc_hba {struct lpfc_io_buf* (* lpfc_get_scsi_buf ) (struct lpfc_hba*,struct lpfc_nodelist*,struct scsi_cmnd*) ;} ;

/* Variables and functions */
 struct lpfc_io_buf* stub1 (struct lpfc_hba*,struct lpfc_nodelist*,struct scsi_cmnd*) ; 

__attribute__((used)) static struct lpfc_io_buf*
lpfc_get_scsi_buf(struct lpfc_hba *phba, struct lpfc_nodelist *ndlp,
		  struct scsi_cmnd *cmnd)
{
	return  phba->lpfc_get_scsi_buf(phba, ndlp, cmnd);
}