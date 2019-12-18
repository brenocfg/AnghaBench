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
struct renesas_usb3_request {int dummy; } ;
struct renesas_usb3_ep {TYPE_1__* dma; } ;
struct renesas_usb3 {int num_usb3_eps; } ;
struct TYPE_2__ {int /*<<< orphan*/  num; } ;

/* Variables and functions */
 int AXI_INT_PRDEN_CLR_STA (int /*<<< orphan*/ ) ; 
 int DMA_INT (int) ; 
 int /*<<< orphan*/  USB3_AXI_INT_STA ; 
 int usb3_dma_try_stop (struct renesas_usb3_ep*,struct renesas_usb3_request*) ; 
 struct renesas_usb3_ep* usb3_get_ep (struct renesas_usb3*,int) ; 
 struct renesas_usb3_request* usb3_get_request (struct renesas_usb3_ep*) ; 
 int usb3_read (struct renesas_usb3*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb3_request_done_pipen (struct renesas_usb3*,struct renesas_usb3_ep*,struct renesas_usb3_request*,int) ; 

__attribute__((used)) static void usb3_irq_dma_int(struct renesas_usb3 *usb3, u32 dma_sta)
{
	struct renesas_usb3_ep *usb3_ep;
	struct renesas_usb3_request *usb3_req;
	int i, status;

	for (i = 0; i < usb3->num_usb3_eps; i++) {
		if (!(dma_sta & DMA_INT(i)))
			continue;

		usb3_ep = usb3_get_ep(usb3, i);
		if (!(usb3_read(usb3, USB3_AXI_INT_STA) &
		    AXI_INT_PRDEN_CLR_STA(usb3_ep->dma->num)))
			continue;

		usb3_req = usb3_get_request(usb3_ep);
		status = usb3_dma_try_stop(usb3_ep, usb3_req);
		usb3_request_done_pipen(usb3, usb3_ep, usb3_req, status);
	}
}