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
#define  ALCHEMY_CPU_AU1000 133 
#define  ALCHEMY_CPU_AU1100 132 
#define  ALCHEMY_CPU_AU1200 131 
#define  ALCHEMY_CPU_AU1300 130 
#define  ALCHEMY_CPU_AU1500 129 
#define  ALCHEMY_CPU_AU1550 128 
 int /*<<< orphan*/  AU1000_OHCICFG ; 
 int /*<<< orphan*/  AU1000_USB_OHCI_PHYS_ADDR ; 
 int /*<<< orphan*/  AU1550_OHCICFG ; 
 int /*<<< orphan*/  AU1550_USB_OHCI_PHYS_ADDR ; 
 int alchemy_get_cputype () ; 
 int /*<<< orphan*/  au1000_usb_pm (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  au1200_usb_pm (int) ; 
 int /*<<< orphan*/  au1300_usb_pm (int) ; 

__attribute__((used)) static void alchemy_usb_pm(int susp)
{
	switch (alchemy_get_cputype()) {
	case ALCHEMY_CPU_AU1000:
	case ALCHEMY_CPU_AU1500:
	case ALCHEMY_CPU_AU1100:
		au1000_usb_pm(AU1000_USB_OHCI_PHYS_ADDR, AU1000_OHCICFG, susp);
		break;
	case ALCHEMY_CPU_AU1550:
		au1000_usb_pm(AU1550_USB_OHCI_PHYS_ADDR, AU1550_OHCICFG, susp);
		break;
	case ALCHEMY_CPU_AU1200:
		au1200_usb_pm(susp);
		break;
	case ALCHEMY_CPU_AU1300:
		au1300_usb_pm(susp);
		break;
	}
}