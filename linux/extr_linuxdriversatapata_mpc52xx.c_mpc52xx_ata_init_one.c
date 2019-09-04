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
struct mpc52xx_ata_priv {int /*<<< orphan*/  ata_irq; TYPE_1__* ata_regs; } ;
struct device {int dummy; } ;
struct ata_ioports {int /*<<< orphan*/ * command_addr; int /*<<< orphan*/ * status_addr; int /*<<< orphan*/ * device_addr; int /*<<< orphan*/ * lbah_addr; int /*<<< orphan*/ * lbam_addr; int /*<<< orphan*/ * lbal_addr; int /*<<< orphan*/ * nsect_addr; int /*<<< orphan*/ * feature_addr; int /*<<< orphan*/ * error_addr; int /*<<< orphan*/ * data_addr; int /*<<< orphan*/ * ctl_addr; int /*<<< orphan*/ * altstatus_addr; int /*<<< orphan*/ * cmd_addr; } ;
struct ata_port {int mwdma_mask; int udma_mask; struct ata_ioports ioaddr; int /*<<< orphan*/ * ops; int /*<<< orphan*/  pio_mask; int /*<<< orphan*/  flags; } ;
struct ata_host {struct mpc52xx_ata_priv* private_data; struct ata_port** ports; } ;
struct TYPE_2__ {int /*<<< orphan*/  tf_command; int /*<<< orphan*/  tf_dev_head; int /*<<< orphan*/  tf_cyl_high; int /*<<< orphan*/  tf_cyl_low; int /*<<< orphan*/  tf_sec_num; int /*<<< orphan*/  tf_sec_count; int /*<<< orphan*/  tf_features; int /*<<< orphan*/  tf_data; int /*<<< orphan*/  tf_control; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATA_FLAG_SLAVE_POSS ; 
 int /*<<< orphan*/  ATA_PIO4 ; 
 int ENOMEM ; 
 int /*<<< orphan*/  ata_bmdma_interrupt ; 
 int ata_host_activate (struct ata_host*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct ata_host* ata_host_alloc (struct device*,int) ; 
 int /*<<< orphan*/  ata_port_desc (struct ata_port*,char*,unsigned long) ; 
 int /*<<< orphan*/  mpc52xx_ata_port_ops ; 
 int /*<<< orphan*/  mpc52xx_ata_sht ; 

__attribute__((used)) static int mpc52xx_ata_init_one(struct device *dev,
				struct mpc52xx_ata_priv *priv,
				unsigned long raw_ata_regs,
				int mwdma_mask, int udma_mask)
{
	struct ata_host *host;
	struct ata_port *ap;
	struct ata_ioports *aio;

	host = ata_host_alloc(dev, 1);
	if (!host)
		return -ENOMEM;

	ap = host->ports[0];
	ap->flags		|= ATA_FLAG_SLAVE_POSS;
	ap->pio_mask		= ATA_PIO4;
	ap->mwdma_mask		= mwdma_mask;
	ap->udma_mask		= udma_mask;
	ap->ops			= &mpc52xx_ata_port_ops;
	host->private_data	= priv;

	aio = &ap->ioaddr;
	aio->cmd_addr		= NULL;	/* Don't have a classic reg block */
	aio->altstatus_addr	= &priv->ata_regs->tf_control;
	aio->ctl_addr		= &priv->ata_regs->tf_control;
	aio->data_addr		= &priv->ata_regs->tf_data;
	aio->error_addr		= &priv->ata_regs->tf_features;
	aio->feature_addr	= &priv->ata_regs->tf_features;
	aio->nsect_addr		= &priv->ata_regs->tf_sec_count;
	aio->lbal_addr		= &priv->ata_regs->tf_sec_num;
	aio->lbam_addr		= &priv->ata_regs->tf_cyl_low;
	aio->lbah_addr		= &priv->ata_regs->tf_cyl_high;
	aio->device_addr	= &priv->ata_regs->tf_dev_head;
	aio->status_addr	= &priv->ata_regs->tf_command;
	aio->command_addr	= &priv->ata_regs->tf_command;

	ata_port_desc(ap, "ata_regs 0x%lx", raw_ata_regs);

	/* activate host */
	return ata_host_activate(host, priv->ata_irq, ata_bmdma_interrupt, 0,
				 &mpc52xx_ata_sht);
}