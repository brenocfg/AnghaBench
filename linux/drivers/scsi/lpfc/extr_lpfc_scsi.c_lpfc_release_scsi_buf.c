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
struct lpfc_io_buf {int flags; TYPE_1__* ndlp; } ;
struct lpfc_hba {int /*<<< orphan*/  (* lpfc_release_scsi_buf ) (struct lpfc_hba*,struct lpfc_io_buf*) ;} ;
struct TYPE_2__ {int /*<<< orphan*/  cmd_pending; } ;

/* Variables and functions */
 int LPFC_SBUF_BUMP_QDEPTH ; 
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct lpfc_hba*,struct lpfc_io_buf*) ; 

__attribute__((used)) static void
lpfc_release_scsi_buf(struct lpfc_hba *phba, struct lpfc_io_buf *psb)
{
	if ((psb->flags & LPFC_SBUF_BUMP_QDEPTH) && psb->ndlp)
		atomic_dec(&psb->ndlp->cmd_pending);

	psb->flags &= ~LPFC_SBUF_BUMP_QDEPTH;
	phba->lpfc_release_scsi_buf(phba, psb);
}