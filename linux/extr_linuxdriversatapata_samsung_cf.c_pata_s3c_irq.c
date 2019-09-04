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
typedef  int /*<<< orphan*/  u32 ;
struct s3c_ide_info {scalar_t__ ide_addr; } ;
struct ata_host {struct s3c_ide_info* private_data; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 scalar_t__ S3C_ATA_IRQ ; 
 int /*<<< orphan*/  ata_sff_interrupt (int,void*) ; 
 int /*<<< orphan*/  readl (scalar_t__) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static irqreturn_t pata_s3c_irq(int irq, void *dev_instance)
{
	struct ata_host *host = dev_instance;
	struct s3c_ide_info *info = host->private_data;
	u32 reg;

	reg = readl(info->ide_addr + S3C_ATA_IRQ);
	writel(reg, info->ide_addr + S3C_ATA_IRQ);

	return ata_sff_interrupt(irq, dev_instance);
}