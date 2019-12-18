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
typedef  int /*<<< orphan*/  u32 ;
struct lpc32xx_udc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_SET_EP_STAT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DAT_WR_BYTE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EP_STAT_ST ; 
 int /*<<< orphan*/  udc_protocol_cmd_data_w (struct lpc32xx_udc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void udc_stall_hwep(struct lpc32xx_udc *udc, u32 hwep)
{
	udc_protocol_cmd_data_w(udc, CMD_SET_EP_STAT(hwep),
				DAT_WR_BYTE(EP_STAT_ST));
}