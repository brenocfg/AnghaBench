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
struct saa7134_dev {TYPE_1__* pci; } ;
struct TYPE_2__ {int device; } ;

/* Variables and functions */
#define  PCI_DEVICE_ID_PHILIPS_SAA7134 128 
 int /*<<< orphan*/  SAA7134_CHANNEL1_LEVEL ; 
 int /*<<< orphan*/  SAA7134_CHANNEL2_LEVEL ; 
 int /*<<< orphan*/  SAA7134_NICAM_LEVEL_ADJUST ; 
 int /*<<< orphan*/  saa_writeb (int /*<<< orphan*/ ,int) ; 

void saa7134_tvaudio_setvolume(struct saa7134_dev *dev, int level)
{
	switch (dev->pci->device) {
	case PCI_DEVICE_ID_PHILIPS_SAA7134:
		saa_writeb(SAA7134_CHANNEL1_LEVEL,     level & 0x1f);
		saa_writeb(SAA7134_CHANNEL2_LEVEL,     level & 0x1f);
		saa_writeb(SAA7134_NICAM_LEVEL_ADJUST, level & 0x1f);
		break;
	}
}