#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  int s8 ;
struct TYPE_3__ {int irq; scalar_t__ channel; } ;
typedef  TYPE_1__ ide_hwif_t ;

/* Variables and functions */
 scalar_t__ isa_dev ; 
 int /*<<< orphan*/  pci_read_config_byte (scalar_t__,int,int*) ; 

__attribute__((used)) static void init_hwif_ali15x3(ide_hwif_t *hwif)
{
	u8 ideic, inmir;
	s8 irq_routing_table[] = { -1,  9, 3, 10, 4,  5, 7,  6,
				      1, 11, 0, 12, 0, 14, 0, 15 };
	int irq = -1;

	if (isa_dev) {
		/*
		 * read IDE interface control
		 */
		pci_read_config_byte(isa_dev, 0x58, &ideic);

		/* bit0, bit1 */
		ideic = ideic & 0x03;

		/* get IRQ for IDE Controller */
		if ((hwif->channel && ideic == 0x03) ||
		    (!hwif->channel && !ideic)) {
			/*
			 * get SIRQ1 routing table
			 */
			pci_read_config_byte(isa_dev, 0x44, &inmir);
			inmir = inmir & 0x0f;
			irq = irq_routing_table[inmir];
		} else if (hwif->channel && !(ideic & 0x01)) {
			/*
			 * get SIRQ2 routing table
			 */
			pci_read_config_byte(isa_dev, 0x75, &inmir);
			inmir = inmir & 0x0f;
			irq = irq_routing_table[inmir];
		}
		if(irq >= 0)
			hwif->irq = irq;
	}
}