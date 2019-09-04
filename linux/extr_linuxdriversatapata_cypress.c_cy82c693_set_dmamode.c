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
struct ata_port {int port_no; } ;
struct ata_device {int dma_mode; } ;

/* Variables and functions */
 int CY82_INDEX_CHANNEL0 ; 
 int CY82_INDEX_TIMEOUT ; 
 int XFER_MW_DMA_0 ; 
 int /*<<< orphan*/  outb (int,int) ; 

__attribute__((used)) static void cy82c693_set_dmamode(struct ata_port *ap, struct ata_device *adev)
{
	int reg = CY82_INDEX_CHANNEL0 + ap->port_no;

	/* Be afraid, be very afraid. Magic registers  in low I/O space */
	outb(reg, 0x22);
	outb(adev->dma_mode - XFER_MW_DMA_0, 0x23);

	/* 0x50 gives the best behaviour on the Alpha's using this chip */
	outb(CY82_INDEX_TIMEOUT, 0x22);
	outb(0x50, 0x23);
}