#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct scsi_cmnd {int /*<<< orphan*/  sc_data_direction; } ;
struct bnx2fc_interface {struct bnx2fc_hba* hba; } ;
struct bnx2fc_hba {TYPE_1__* pcidev; } ;
struct bnx2fc_cmd {TYPE_3__* bd_tbl; TYPE_2__* port; struct scsi_cmnd* sc_cmd; } ;
struct TYPE_6__ {scalar_t__ bd_valid; } ;
struct TYPE_5__ {struct bnx2fc_interface* priv; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dma_unmap_sg (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ scsi_sg_count (struct scsi_cmnd*) ; 
 int /*<<< orphan*/  scsi_sglist (struct scsi_cmnd*) ; 

__attribute__((used)) static void bnx2fc_unmap_sg_list(struct bnx2fc_cmd *io_req)
{
	struct scsi_cmnd *sc = io_req->sc_cmd;
	struct bnx2fc_interface *interface = io_req->port->priv;
	struct bnx2fc_hba *hba = interface->hba;

	/*
	 * Use dma_unmap_sg directly to ensure we're using the correct
	 * dev struct off of pcidev.
	 */
	if (io_req->bd_tbl->bd_valid && sc && scsi_sg_count(sc)) {
		dma_unmap_sg(&hba->pcidev->dev, scsi_sglist(sc),
		    scsi_sg_count(sc), sc->sc_data_direction);
		io_req->bd_tbl->bd_valid = 0;
	}
}