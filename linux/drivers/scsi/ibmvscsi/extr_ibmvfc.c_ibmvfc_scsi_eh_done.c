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
struct scsi_cmnd {int /*<<< orphan*/  (* scsi_done ) (struct scsi_cmnd*) ;} ;
struct ibmvfc_event {scalar_t__ eh_comp; struct scsi_cmnd* cmnd; } ;

/* Variables and functions */
 int /*<<< orphan*/  complete (scalar_t__) ; 
 int /*<<< orphan*/  ibmvfc_free_event (struct ibmvfc_event*) ; 
 int /*<<< orphan*/  scsi_dma_unmap (struct scsi_cmnd*) ; 
 int /*<<< orphan*/  stub1 (struct scsi_cmnd*) ; 

__attribute__((used)) static void ibmvfc_scsi_eh_done(struct ibmvfc_event *evt)
{
	struct scsi_cmnd *cmnd = evt->cmnd;

	if (cmnd) {
		scsi_dma_unmap(cmnd);
		cmnd->scsi_done(cmnd);
	}

	if (evt->eh_comp)
		complete(evt->eh_comp);

	ibmvfc_free_event(evt);
}