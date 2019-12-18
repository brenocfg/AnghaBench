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
typedef  int u32 ;
struct TYPE_2__ {scalar_t__ speed; } ;
struct lpc32xx_udc {scalar_t__ vbus; int poweron; int /*<<< orphan*/  pullup_job; scalar_t__ driver; TYPE_1__ gadget; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_GET_DEV_STAT ; 
 int /*<<< orphan*/  DAT_GET_DEV_STAT ; 
 int DEV_CON ; 
 int DEV_CON_CH ; 
 int DEV_RST ; 
 int DEV_SUS ; 
 int DEV_SUS_CH ; 
 scalar_t__ USB_SPEED_UNKNOWN ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stop_activity (struct lpc32xx_udc*) ; 
 int /*<<< orphan*/  uda_power_event (struct lpc32xx_udc*,int) ; 
 int /*<<< orphan*/  uda_resm_susp_event (struct lpc32xx_udc*,int) ; 
 int /*<<< orphan*/  uda_usb_reset (struct lpc32xx_udc*) ; 
 int udc_protocol_cmd_r (struct lpc32xx_udc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udc_protocol_cmd_w (struct lpc32xx_udc*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void udc_handle_dev(struct lpc32xx_udc *udc)
{
	u32 tmp;

	udc_protocol_cmd_w(udc, CMD_GET_DEV_STAT);
	tmp = udc_protocol_cmd_r(udc, DAT_GET_DEV_STAT);

	if (tmp & DEV_RST)
		uda_usb_reset(udc);
	else if (tmp & DEV_CON_CH)
		uda_power_event(udc, (tmp & DEV_CON));
	else if (tmp & DEV_SUS_CH) {
		if (tmp & DEV_SUS) {
			if (udc->vbus == 0)
				stop_activity(udc);
			else if ((udc->gadget.speed != USB_SPEED_UNKNOWN) &&
				 udc->driver) {
				/* Power down transceiver */
				udc->poweron = 0;
				schedule_work(&udc->pullup_job);
				uda_resm_susp_event(udc, 1);
			}
		} else if ((udc->gadget.speed != USB_SPEED_UNKNOWN) &&
			   udc->driver && udc->vbus) {
			uda_resm_susp_event(udc, 0);
			/* Power up transceiver */
			udc->poweron = 1;
			schedule_work(&udc->pullup_job);
		}
	}
}