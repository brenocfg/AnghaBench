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
typedef  enum cvmx_helper_board_usb_clock_types { ____Placeholder_cvmx_helper_board_usb_clock_types } cvmx_helper_board_usb_clock_types ;
struct TYPE_2__ {int board_type; } ;

/* Variables and functions */
#define  CVMX_BOARD_TYPE_BBGW_REF 134 
#define  CVMX_BOARD_TYPE_LANAI2_A 133 
#define  CVMX_BOARD_TYPE_LANAI2_G 132 
#define  CVMX_BOARD_TYPE_LANAI2_U 131 
#define  CVMX_BOARD_TYPE_NIC10E 130 
#define  CVMX_BOARD_TYPE_NIC10E_66 129 
#define  CVMX_BOARD_TYPE_UBNT_E100 128 
 scalar_t__ OCTEON_IS_OCTEON2 () ; 
 int USB_CLOCK_TYPE_CRYSTAL_12 ; 
 int USB_CLOCK_TYPE_REF_12 ; 
 int USB_CLOCK_TYPE_REF_48 ; 
 TYPE_1__* cvmx_sysinfo_get () ; 

enum cvmx_helper_board_usb_clock_types __cvmx_helper_board_usb_get_clock_type(void)
{
	switch (cvmx_sysinfo_get()->board_type) {
	case CVMX_BOARD_TYPE_BBGW_REF:
	case CVMX_BOARD_TYPE_LANAI2_A:
	case CVMX_BOARD_TYPE_LANAI2_U:
	case CVMX_BOARD_TYPE_LANAI2_G:
	case CVMX_BOARD_TYPE_NIC10E_66:
	case CVMX_BOARD_TYPE_UBNT_E100:
		return USB_CLOCK_TYPE_CRYSTAL_12;
	case CVMX_BOARD_TYPE_NIC10E:
		return USB_CLOCK_TYPE_REF_12;
	default:
		break;
	}
	/* Most boards except NIC10e use a 12MHz crystal */
	if (OCTEON_IS_OCTEON2())
		return USB_CLOCK_TYPE_CRYSTAL_12;
	return USB_CLOCK_TYPE_REF_48;
}