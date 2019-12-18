#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  usb_type_max; int /*<<< orphan*/  set_max; } ;
struct TYPE_3__ {int usb_current; } ;
struct ab8500_charger {TYPE_2__ max_usb_in_curr; TYPE_1__ usb_state; } ;

/* Variables and functions */
 int EPERM ; 
 int /*<<< orphan*/  USB_CH_IP_CUR_LVL_0P05 ; 
 int /*<<< orphan*/  USB_CH_IP_CUR_LVL_0P09 ; 
 int /*<<< orphan*/  USB_CH_IP_CUR_LVL_0P19 ; 
 int /*<<< orphan*/  USB_CH_IP_CUR_LVL_0P29 ; 
 int /*<<< orphan*/  USB_CH_IP_CUR_LVL_0P38 ; 
 int /*<<< orphan*/  USB_CH_IP_CUR_LVL_0P5 ; 

__attribute__((used)) static int ab8500_charger_get_usb_cur(struct ab8500_charger *di)
{
	int ret = 0;
	switch (di->usb_state.usb_current) {
	case 100:
		di->max_usb_in_curr.usb_type_max = USB_CH_IP_CUR_LVL_0P09;
		break;
	case 200:
		di->max_usb_in_curr.usb_type_max = USB_CH_IP_CUR_LVL_0P19;
		break;
	case 300:
		di->max_usb_in_curr.usb_type_max = USB_CH_IP_CUR_LVL_0P29;
		break;
	case 400:
		di->max_usb_in_curr.usb_type_max = USB_CH_IP_CUR_LVL_0P38;
		break;
	case 500:
		di->max_usb_in_curr.usb_type_max = USB_CH_IP_CUR_LVL_0P5;
		break;
	default:
		di->max_usb_in_curr.usb_type_max = USB_CH_IP_CUR_LVL_0P05;
		ret = -EPERM;
		break;
	};
	di->max_usb_in_curr.set_max = di->max_usb_in_curr.usb_type_max;
	return ret;
}