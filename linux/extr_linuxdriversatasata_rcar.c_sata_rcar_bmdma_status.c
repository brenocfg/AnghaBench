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
typedef  int /*<<< orphan*/  u8 ;
typedef  int u32 ;
struct sata_rcar_priv {scalar_t__ base; } ;
struct ata_port {TYPE_1__* host; } ;
struct TYPE_2__ {struct sata_rcar_priv* private_data; } ;

/* Variables and functions */
 int ATAPI_STATUS_ACT ; 
 int ATAPI_STATUS_DEVINT ; 
 scalar_t__ ATAPI_STATUS_REG ; 
 int /*<<< orphan*/  ATA_DMA_ACTIVE ; 
 int /*<<< orphan*/  ATA_DMA_INTR ; 
 int ioread32 (scalar_t__) ; 

__attribute__((used)) static u8 sata_rcar_bmdma_status(struct ata_port *ap)
{
	struct sata_rcar_priv *priv = ap->host->private_data;
	u8 host_stat = 0;
	u32 status;

	status = ioread32(priv->base + ATAPI_STATUS_REG);
	if (status & ATAPI_STATUS_DEVINT)
		host_stat |= ATA_DMA_INTR;
	if (status & ATAPI_STATUS_ACT)
		host_stat |= ATA_DMA_ACTIVE;

	return host_stat;
}