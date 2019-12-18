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
struct pxa25x_ep {int bEndpointAddress; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  UICR0 ; 
 int /*<<< orphan*/  UICR1 ; 
 int udc_get_reg (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udc_set_reg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void pio_irq_enable(struct pxa25x_ep *ep)
{
	u32 bEndpointAddress = ep->bEndpointAddress & 0xf;

        if (bEndpointAddress < 8)
		udc_set_reg(ep->dev, UICR0, udc_get_reg(ep->dev, UICR0) &
						~(1 << bEndpointAddress));
        else {
                bEndpointAddress -= 8;
		udc_set_reg(ep->dev, UICR1, udc_get_reg(ep->dev, UICR1) &
						~(1 << bEndpointAddress));
	}
}