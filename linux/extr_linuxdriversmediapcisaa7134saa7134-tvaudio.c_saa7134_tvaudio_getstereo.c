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
struct saa7134_dev {int /*<<< orphan*/  tvaudio; TYPE_1__* pci; } ;
struct TYPE_2__ {int device; } ;

/* Variables and functions */
#define  PCI_DEVICE_ID_PHILIPS_SAA7133 130 
#define  PCI_DEVICE_ID_PHILIPS_SAA7134 129 
#define  PCI_DEVICE_ID_PHILIPS_SAA7135 128 
 int V4L2_TUNER_SUB_MONO ; 
 int getstereo_7133 (struct saa7134_dev*) ; 
 int tvaudio_getstereo (struct saa7134_dev*,int /*<<< orphan*/ ) ; 

int saa7134_tvaudio_getstereo(struct saa7134_dev *dev)
{
	int retval = V4L2_TUNER_SUB_MONO;

	switch (dev->pci->device) {
	case PCI_DEVICE_ID_PHILIPS_SAA7134:
		if (dev->tvaudio)
			retval = tvaudio_getstereo(dev,dev->tvaudio);
		break;
	case PCI_DEVICE_ID_PHILIPS_SAA7133:
	case PCI_DEVICE_ID_PHILIPS_SAA7135:
		retval = getstereo_7133(dev);
		break;
	}
	return retval;
}