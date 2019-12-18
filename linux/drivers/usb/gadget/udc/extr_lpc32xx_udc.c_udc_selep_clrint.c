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
 int /*<<< orphan*/  CMD_SEL_EP_CLRI (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DAT_SEL_EP_CLRI (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udc_protocol_cmd_r (struct lpc32xx_udc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udc_protocol_cmd_w (struct lpc32xx_udc*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static u32 udc_selep_clrint(struct lpc32xx_udc *udc, u32 hwep)
{
	udc_protocol_cmd_w(udc, CMD_SEL_EP_CLRI(hwep));
	return udc_protocol_cmd_r(udc, DAT_SEL_EP_CLRI(hwep));
}