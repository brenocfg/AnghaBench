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
struct TYPE_2__ {int sversion; } ;
struct parisc_device {int hw_path; int /*<<< orphan*/  irq; TYPE_1__ id; } ;

/* Variables and functions */
 int /*<<< orphan*/  gsc_asic_assign_irq (void*,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void lasi_choose_irq(struct parisc_device *dev, void *ctrl)
{
	int irq;

	switch (dev->id.sversion) {
		case 0x74:	irq =  7; break; /* Centronics */
		case 0x7B:	irq = 13; break; /* Audio */
		case 0x81:	irq = 14; break; /* Lasi itself */
		case 0x82:	irq =  9; break; /* SCSI */
		case 0x83:	irq = 20; break; /* Floppy */
		case 0x84:	irq = 26; break; /* PS/2 Keyboard */
		case 0x87:	irq = 18; break; /* ISDN */
		case 0x8A:	irq =  8; break; /* LAN */
		case 0x8C:	irq =  5; break; /* RS232 */
		case 0x8D:	irq = (dev->hw_path == 13) ? 16 : 17; break;
						 /* Telephone */
		default: 	return;		 /* unknown */
	}

	gsc_asic_assign_irq(ctrl, irq, &dev->irq);
}