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
typedef  int u32 ;
struct TYPE_6__ {int flags; int /*<<< orphan*/  protocol; } ;
struct ata_queued_cmd {int hw_tag; int flags; TYPE_3__ tf; TYPE_2__* dev; int /*<<< orphan*/  cdb; struct ata_port* ap; } ;
struct ata_port {struct ahci_port_priv* private_data; } ;
struct ahci_port_priv {void* cmd_tbl; } ;
struct TYPE_5__ {TYPE_1__* link; int /*<<< orphan*/  cdb_len; } ;
struct TYPE_4__ {int pmp; } ;

/* Variables and functions */
 int AHCI_CMD_ATAPI ; 
 int AHCI_CMD_PREFETCH ; 
 int AHCI_CMD_TBL_CDB ; 
 int AHCI_CMD_TBL_SZ ; 
 int AHCI_CMD_WRITE ; 
 int ATA_QCFLAG_DMAMAP ; 
 int ATA_TFLAG_WRITE ; 
 unsigned int acard_ahci_fill_sg (struct ata_queued_cmd*,void*) ; 
 int /*<<< orphan*/  ahci_fill_cmd_slot (struct ahci_port_priv*,int,int) ; 
 int ata_is_atapi (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ata_tf_to_fis (TYPE_3__*,int,int,void*) ; 
 int /*<<< orphan*/  memcpy (void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (void*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void acard_ahci_qc_prep(struct ata_queued_cmd *qc)
{
	struct ata_port *ap = qc->ap;
	struct ahci_port_priv *pp = ap->private_data;
	int is_atapi = ata_is_atapi(qc->tf.protocol);
	void *cmd_tbl;
	u32 opts;
	const u32 cmd_fis_len = 5; /* five dwords */
	unsigned int n_elem;

	/*
	 * Fill in command table information.  First, the header,
	 * a SATA Register - Host to Device command FIS.
	 */
	cmd_tbl = pp->cmd_tbl + qc->hw_tag * AHCI_CMD_TBL_SZ;

	ata_tf_to_fis(&qc->tf, qc->dev->link->pmp, 1, cmd_tbl);
	if (is_atapi) {
		memset(cmd_tbl + AHCI_CMD_TBL_CDB, 0, 32);
		memcpy(cmd_tbl + AHCI_CMD_TBL_CDB, qc->cdb, qc->dev->cdb_len);
	}

	n_elem = 0;
	if (qc->flags & ATA_QCFLAG_DMAMAP)
		n_elem = acard_ahci_fill_sg(qc, cmd_tbl);

	/*
	 * Fill in command slot information.
	 *
	 * ACard note: prd table length not filled in
	 */
	opts = cmd_fis_len | (qc->dev->link->pmp << 12);
	if (qc->tf.flags & ATA_TFLAG_WRITE)
		opts |= AHCI_CMD_WRITE;
	if (is_atapi)
		opts |= AHCI_CMD_ATAPI | AHCI_CMD_PREFETCH;

	ahci_fill_cmd_slot(pp, qc->hw_tag, opts);
}