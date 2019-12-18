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
struct lpc32xx_udc {int dummy; } ;
struct lpc32xx_ep {int /*<<< orphan*/  hwep_num; } ;

/* Variables and functions */
 int /*<<< orphan*/  udc_clearep_getsts (struct lpc32xx_udc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udc_write_hwep (struct lpc32xx_udc*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void udc_send_in_zlp(struct lpc32xx_udc *udc, struct lpc32xx_ep *ep)
{
	/* Clear EP status */
	udc_clearep_getsts(udc, ep->hwep_num);

	/* Send ZLP via FIFO mechanism */
	udc_write_hwep(udc, ep->hwep_num, NULL, 0);
}