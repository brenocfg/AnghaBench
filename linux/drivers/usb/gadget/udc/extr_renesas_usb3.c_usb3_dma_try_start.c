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
struct renesas_usb3_request {int dummy; } ;
struct renesas_usb3_ep {int dummy; } ;
struct renesas_usb3 {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  usb3_dma_fill_prd (struct renesas_usb3_ep*,struct renesas_usb3_request*) ; 
 scalar_t__ usb3_dma_get_setting_area (struct renesas_usb3_ep*,struct renesas_usb3_request*) ; 
 int /*<<< orphan*/  usb3_dma_kick_prd (struct renesas_usb3_ep*) ; 
 int /*<<< orphan*/  usb3_enable_dma_pipen (struct renesas_usb3*) ; 
 struct renesas_usb3* usb3_ep_to_usb3 (struct renesas_usb3_ep*) ; 
 int /*<<< orphan*/  usb3_pn_start (struct renesas_usb3*) ; 
 int /*<<< orphan*/  usb3_pn_stop (struct renesas_usb3*) ; 
 int /*<<< orphan*/  use_dma ; 

__attribute__((used)) static bool usb3_dma_try_start(struct renesas_usb3_ep *usb3_ep,
			       struct renesas_usb3_request *usb3_req)
{
	struct renesas_usb3 *usb3 = usb3_ep_to_usb3(usb3_ep);

	if (!use_dma)
		return false;

	if (usb3_dma_get_setting_area(usb3_ep, usb3_req)) {
		usb3_pn_stop(usb3);
		usb3_enable_dma_pipen(usb3);
		usb3_dma_fill_prd(usb3_ep, usb3_req);
		usb3_dma_kick_prd(usb3_ep);
		usb3_pn_start(usb3);
		return true;
	}

	return false;
}