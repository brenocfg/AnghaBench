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
typedef  int u32 ;
typedef  enum usb_device_speed { ____Placeholder_usb_device_speed } usb_device_speed ;

/* Variables and functions */
 int USB_ISTS_CON2I ; 
 int USB_ISTS_CONI ; 
 int USB_ISTS_DIS2I ; 
 int USB_ISTS_DISI ; 
 int USB_ISTS_L1ENTI ; 
 int USB_ISTS_L1EXTI ; 
 int USB_ISTS_L2ENTI ; 
 int USB_ISTS_L2EXTI ; 
 int USB_ISTS_U2RESI ; 
 int USB_ISTS_U3EXTI ; 
 int USB_ISTS_UHRESI ; 
 int USB_ISTS_UWRESI ; 
 int sprintf (char*,char*,...) ; 
 char* usb_speed_string (int) ; 

__attribute__((used)) static inline char *cdns3_decode_usb_irq(char *str,
					 enum usb_device_speed speed,
					 u32 usb_ists)
{
	int ret;

	ret = sprintf(str, "IRQ %08x = ", usb_ists);

	if (usb_ists & (USB_ISTS_CON2I | USB_ISTS_CONI)) {
		ret += sprintf(str + ret, "Connection %s\n",
			       usb_speed_string(speed));
	}
	if (usb_ists & USB_ISTS_DIS2I || usb_ists & USB_ISTS_DISI)
		ret += sprintf(str + ret, "Disconnection ");
	if (usb_ists & USB_ISTS_L2ENTI)
		ret += sprintf(str + ret, "suspended ");
	if (usb_ists & USB_ISTS_L1ENTI)
		ret += sprintf(str + ret, "L1 enter ");
	if (usb_ists & USB_ISTS_L1EXTI)
		ret += sprintf(str + ret, "L1 exit ");
	if (usb_ists & USB_ISTS_L2ENTI)
		ret += sprintf(str + ret, "L2 enter ");
	if (usb_ists & USB_ISTS_L2EXTI)
		ret += sprintf(str + ret, "L2 exit ");
	if (usb_ists & USB_ISTS_U3EXTI)
		ret += sprintf(str + ret, "U3 exit ");
	if (usb_ists & USB_ISTS_UWRESI)
		ret += sprintf(str + ret, "Warm Reset ");
	if (usb_ists & USB_ISTS_UHRESI)
		ret += sprintf(str + ret, "Hot Reset ");
	if (usb_ists & USB_ISTS_U2RESI)
		ret += sprintf(str + ret, "Reset");

	return str;
}