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
struct r8152 {int coalesce; int version; } ;

/* Variables and functions */
 int /*<<< orphan*/  MCU_TYPE_USB ; 
#define  RTL_VER_03 133 
#define  RTL_VER_04 132 
#define  RTL_VER_05 131 
#define  RTL_VER_06 130 
#define  RTL_VER_08 129 
#define  RTL_VER_09 128 
 int /*<<< orphan*/  USB_RX_EARLY_TIMEOUT ; 
 int /*<<< orphan*/  USB_RX_EXTRA_AGGR_TMR ; 
 int /*<<< orphan*/  ocp_write_word (struct r8152*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void r8153_set_rx_early_timeout(struct r8152 *tp)
{
	u32 ocp_data = tp->coalesce / 8;

	switch (tp->version) {
	case RTL_VER_03:
	case RTL_VER_04:
	case RTL_VER_05:
	case RTL_VER_06:
		ocp_write_word(tp, MCU_TYPE_USB, USB_RX_EARLY_TIMEOUT,
			       ocp_data);
		break;

	case RTL_VER_08:
	case RTL_VER_09:
		/* The RTL8153B uses USB_RX_EXTRA_AGGR_TMR for rx timeout
		 * primarily. For USB_RX_EARLY_TIMEOUT, we fix it to 128ns.
		 */
		ocp_write_word(tp, MCU_TYPE_USB, USB_RX_EARLY_TIMEOUT,
			       128 / 8);
		ocp_write_word(tp, MCU_TYPE_USB, USB_RX_EXTRA_AGGR_TMR,
			       ocp_data);
		break;

	default:
		break;
	}
}