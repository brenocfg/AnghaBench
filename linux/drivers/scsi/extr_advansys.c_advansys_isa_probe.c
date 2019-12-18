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
struct device {int dummy; } ;
struct asc_board {struct Scsi_Host* shost; struct device* dev; int /*<<< orphan*/  irq; } ;
struct Scsi_Host {int dummy; } ;
typedef  int /*<<< orphan*/  PortAddr ;

/* Variables and functions */
 int ASC_CHIP_VER_ISA_BIT ; 
 int /*<<< orphan*/  ASC_DBG (int,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ASC_IOADR_GAP ; 
 int /*<<< orphan*/  ASC_IS_ISA ; 
 int /*<<< orphan*/  AscFindSignature (int /*<<< orphan*/ ) ; 
 int AscGetChipVersion (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DRV_NAME ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/ * _asc_def_iop_base ; 
 int advansys_board_found (struct Scsi_Host*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  advansys_isa_irq_no (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  advansys_template ; 
 int /*<<< orphan*/  dev_set_drvdata (struct device*,struct Scsi_Host*) ; 
 int /*<<< orphan*/  release_region (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  request_region (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct Scsi_Host* scsi_host_alloc (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  scsi_host_put (struct Scsi_Host*) ; 
 struct asc_board* shost_priv (struct Scsi_Host*) ; 

__attribute__((used)) static int advansys_isa_probe(struct device *dev, unsigned int id)
{
	int err = -ENODEV;
	PortAddr iop_base = _asc_def_iop_base[id];
	struct Scsi_Host *shost;
	struct asc_board *board;

	if (!request_region(iop_base, ASC_IOADR_GAP, DRV_NAME)) {
		ASC_DBG(1, "I/O port 0x%x busy\n", iop_base);
		return -ENODEV;
	}
	ASC_DBG(1, "probing I/O port 0x%x\n", iop_base);
	if (!AscFindSignature(iop_base))
		goto release_region;
	if (!(AscGetChipVersion(iop_base, ASC_IS_ISA) & ASC_CHIP_VER_ISA_BIT))
		goto release_region;

	err = -ENOMEM;
	shost = scsi_host_alloc(&advansys_template, sizeof(*board));
	if (!shost)
		goto release_region;

	board = shost_priv(shost);
	board->irq = advansys_isa_irq_no(iop_base);
	board->dev = dev;
	board->shost = shost;

	err = advansys_board_found(shost, iop_base, ASC_IS_ISA);
	if (err)
		goto free_host;

	dev_set_drvdata(dev, shost);
	return 0;

 free_host:
	scsi_host_put(shost);
 release_region:
	release_region(iop_base, ASC_IOADR_GAP);
	return err;
}