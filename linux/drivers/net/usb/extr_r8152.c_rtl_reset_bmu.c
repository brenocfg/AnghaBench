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
struct r8152 {int dummy; } ;

/* Variables and functions */
 int BMU_RESET_EP_IN ; 
 int BMU_RESET_EP_OUT ; 
 int /*<<< orphan*/  MCU_TYPE_USB ; 
 int /*<<< orphan*/  USB_BMU_RESET ; 
 int ocp_read_byte (struct r8152*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ocp_write_byte (struct r8152*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void rtl_reset_bmu(struct r8152 *tp)
{
	u32 ocp_data;

	ocp_data = ocp_read_byte(tp, MCU_TYPE_USB, USB_BMU_RESET);
	ocp_data &= ~(BMU_RESET_EP_IN | BMU_RESET_EP_OUT);
	ocp_write_byte(tp, MCU_TYPE_USB, USB_BMU_RESET, ocp_data);
	ocp_data |= BMU_RESET_EP_IN | BMU_RESET_EP_OUT;
	ocp_write_byte(tp, MCU_TYPE_USB, USB_BMU_RESET, ocp_data);
}