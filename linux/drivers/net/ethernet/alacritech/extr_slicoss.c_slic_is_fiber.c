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

/* Variables and functions */
#define  PCI_SUBDEVICE_ID_ALACRITECH_1000X1F 133 
#define  PCI_SUBDEVICE_ID_ALACRITECH_SEN2001XF 132 
#define  PCI_SUBDEVICE_ID_ALACRITECH_SEN2002XF 131 
#define  PCI_SUBDEVICE_ID_ALACRITECH_SEN2102EF 130 
#define  PCI_SUBDEVICE_ID_ALACRITECH_SEN2104EF 129 
#define  PCI_SUBDEVICE_ID_ALACRITECH_SES1001F 128 

__attribute__((used)) static bool slic_is_fiber(unsigned short subdev)
{
	switch (subdev) {
	/* Mojave */
	case PCI_SUBDEVICE_ID_ALACRITECH_1000X1F: /* fallthrough */
	case PCI_SUBDEVICE_ID_ALACRITECH_SES1001F: /* fallthrough */
	/* Oasis */
	case PCI_SUBDEVICE_ID_ALACRITECH_SEN2002XF: /* fallthrough */
	case PCI_SUBDEVICE_ID_ALACRITECH_SEN2001XF: /* fallthrough */
	case PCI_SUBDEVICE_ID_ALACRITECH_SEN2104EF: /* fallthrough */
	case PCI_SUBDEVICE_ID_ALACRITECH_SEN2102EF: /* fallthrough */
		return true;
	}
	return false;
}