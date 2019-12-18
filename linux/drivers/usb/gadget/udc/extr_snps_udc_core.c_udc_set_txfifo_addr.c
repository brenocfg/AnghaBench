#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u32 ;
struct udc_ep {int num; int /*<<< orphan*/  txfifo; struct udc* dev; int /*<<< orphan*/  in; } ;
struct udc {TYPE_2__* ep; int /*<<< orphan*/  txfifo; } ;
struct TYPE_4__ {TYPE_1__* regs; } ;
struct TYPE_3__ {int /*<<< orphan*/  bufin_framenum; } ;

/* Variables and functions */
 scalar_t__ AMD_GETBITS (scalar_t__,int /*<<< orphan*/ ) ; 
 int EINVAL ; 
 int /*<<< orphan*/  UDC_EPIN_BUFF_SIZE ; 
 scalar_t__ readl (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int udc_set_txfifo_addr(struct udc_ep *ep)
{
	struct udc	*dev;
	u32 tmp;
	int i;

	if (!ep || !(ep->in))
		return -EINVAL;

	dev = ep->dev;
	ep->txfifo = dev->txfifo;

	/* traverse ep's */
	for (i = 0; i < ep->num; i++) {
		if (dev->ep[i].regs) {
			/* read fifo size */
			tmp = readl(&dev->ep[i].regs->bufin_framenum);
			tmp = AMD_GETBITS(tmp, UDC_EPIN_BUFF_SIZE);
			ep->txfifo += tmp;
		}
	}
	return 0;
}