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
struct ep93xx_pata_data {int dummy; } ;
struct ata_taskfile {int flags; int ctl; void* hob_lbah; void* hob_lbam; void* hob_lbal; void* hob_nsect; void* hob_feature; void* device; void* lbah; void* lbam; void* lbal; void* nsect; void* feature; int /*<<< orphan*/  command; } ;
struct ata_port {int last_ctl; TYPE_1__* host; } ;
struct TYPE_2__ {struct ep93xx_pata_data* private_data; } ;

/* Variables and functions */
 int ATA_HOB ; 
 int ATA_TFLAG_LBA48 ; 
 int /*<<< orphan*/  IDECTRL_ADDR_CTL ; 
 int /*<<< orphan*/  IDECTRL_ADDR_DEVICE ; 
 int /*<<< orphan*/  IDECTRL_ADDR_FEATURE ; 
 int /*<<< orphan*/  IDECTRL_ADDR_LBAH ; 
 int /*<<< orphan*/  IDECTRL_ADDR_LBAL ; 
 int /*<<< orphan*/  IDECTRL_ADDR_LBAM ; 
 int /*<<< orphan*/  IDECTRL_ADDR_NSECT ; 
 int /*<<< orphan*/  ep93xx_pata_check_status (struct ata_port*) ; 
 void* ep93xx_pata_read_reg (struct ep93xx_pata_data*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ep93xx_pata_write_reg (struct ep93xx_pata_data*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ep93xx_pata_tf_read(struct ata_port *ap, struct ata_taskfile *tf)
{
	struct ep93xx_pata_data *drv_data = ap->host->private_data;

	tf->command = ep93xx_pata_check_status(ap);
	tf->feature = ep93xx_pata_read_reg(drv_data, IDECTRL_ADDR_FEATURE);
	tf->nsect = ep93xx_pata_read_reg(drv_data, IDECTRL_ADDR_NSECT);
	tf->lbal = ep93xx_pata_read_reg(drv_data, IDECTRL_ADDR_LBAL);
	tf->lbam = ep93xx_pata_read_reg(drv_data, IDECTRL_ADDR_LBAM);
	tf->lbah = ep93xx_pata_read_reg(drv_data, IDECTRL_ADDR_LBAH);
	tf->device = ep93xx_pata_read_reg(drv_data, IDECTRL_ADDR_DEVICE);

	if (tf->flags & ATA_TFLAG_LBA48) {
		ep93xx_pata_write_reg(drv_data, tf->ctl | ATA_HOB,
			IDECTRL_ADDR_CTL);
		tf->hob_feature = ep93xx_pata_read_reg(drv_data,
			IDECTRL_ADDR_FEATURE);
		tf->hob_nsect = ep93xx_pata_read_reg(drv_data,
			IDECTRL_ADDR_NSECT);
		tf->hob_lbal = ep93xx_pata_read_reg(drv_data,
			IDECTRL_ADDR_LBAL);
		tf->hob_lbam = ep93xx_pata_read_reg(drv_data,
			IDECTRL_ADDR_LBAM);
		tf->hob_lbah = ep93xx_pata_read_reg(drv_data,
			IDECTRL_ADDR_LBAH);
		ep93xx_pata_write_reg(drv_data, tf->ctl, IDECTRL_ADDR_CTL);
		ap->last_ctl = tf->ctl;
	}
}