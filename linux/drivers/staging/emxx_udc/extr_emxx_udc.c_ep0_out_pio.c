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
union usb_reg_access {int /*<<< orphan*/  dw; } ;
typedef  int /*<<< orphan*/  u8 ;
typedef  int u32 ;
struct nbu2ss_udc {TYPE_1__* p_regs; } ;
struct TYPE_2__ {int /*<<< orphan*/  EP0_READ; } ;

/* Variables and functions */
 int /*<<< orphan*/  _nbu2ss_readl (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ep0_out_pio(struct nbu2ss_udc *udc, u8 *buf, u32 length)
{
	u32		i;
	u32 numreads = length / sizeof(u32);
	union usb_reg_access *buf32 = (union usb_reg_access *)buf;

	if (!numreads)
		return 0;

	/* PIO Read */
	for (i = 0; i < numreads; i++) {
		buf32->dw = _nbu2ss_readl(&udc->p_regs->EP0_READ);
		buf32++;
	}

	return  numreads * sizeof(u32);
}