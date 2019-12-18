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
struct at91_udc {TYPE_1__* caps; int /*<<< orphan*/  vbus; int /*<<< orphan*/  enabled; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* pullup ) (struct at91_udc*,int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  AT91_UDP_ICR ; 
 int /*<<< orphan*/  AT91_UDP_IDR ; 
 int /*<<< orphan*/  AT91_UDP_RXRSM ; 
 int /*<<< orphan*/  AT91_UDP_TXVC ; 
 int /*<<< orphan*/  AT91_UDP_TXVC_TXVDIS ; 
 int /*<<< orphan*/  DBG (char*,char*) ; 
 int /*<<< orphan*/  at91_udp_write (struct at91_udc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clk_off (struct at91_udc*) ; 
 int /*<<< orphan*/  clk_on (struct at91_udc*) ; 
 int /*<<< orphan*/  stop_activity (struct at91_udc*) ; 
 int /*<<< orphan*/  stub1 (struct at91_udc*,int) ; 

__attribute__((used)) static void pullup(struct at91_udc *udc, int is_on)
{
	if (!udc->enabled || !udc->vbus)
		is_on = 0;
	DBG("%sactive\n", is_on ? "" : "in");

	if (is_on) {
		clk_on(udc);
		at91_udp_write(udc, AT91_UDP_ICR, AT91_UDP_RXRSM);
		at91_udp_write(udc, AT91_UDP_TXVC, 0);
	} else {
		stop_activity(udc);
		at91_udp_write(udc, AT91_UDP_IDR, AT91_UDP_RXRSM);
		at91_udp_write(udc, AT91_UDP_TXVC, AT91_UDP_TXVC_TXVDIS);
		clk_off(udc);
	}

	if (udc->caps && udc->caps->pullup)
		udc->caps->pullup(udc, is_on);
}