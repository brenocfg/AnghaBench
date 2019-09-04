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
typedef  int /*<<< orphan*/  u8 ;
typedef  scalar_t__ u32 ;

/* Variables and functions */
 int /*<<< orphan*/  ATA_CMD_TRUSTED_NONDATA ; 
 int /*<<< orphan*/  ATA_CMD_TRUSTED_RCV ; 
 int /*<<< orphan*/  ATA_CMD_TRUSTED_RCV_DMA ; 
 int /*<<< orphan*/  ATA_CMD_TRUSTED_SND ; 
 int /*<<< orphan*/  ATA_CMD_TRUSTED_SND_DMA ; 

__attribute__((used)) static u8 ata_scsi_trusted_op(u32 len, bool send, bool dma)
{
	if (len == 0)
		return ATA_CMD_TRUSTED_NONDATA;
	else if (send)
		return dma ? ATA_CMD_TRUSTED_SND_DMA : ATA_CMD_TRUSTED_SND;
	else
		return dma ? ATA_CMD_TRUSTED_RCV_DMA : ATA_CMD_TRUSTED_RCV;
}