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
struct usbhs_pkt {int dummy; } ;

/* Variables and functions */
 int usbhsf_prepare_pop (struct usbhs_pkt*,int*) ; 

__attribute__((used)) static int usbhsf_dma_prepare_pop_with_rx_irq(struct usbhs_pkt *pkt,
					      int *is_done)
{
	return usbhsf_prepare_pop(pkt, is_done);
}