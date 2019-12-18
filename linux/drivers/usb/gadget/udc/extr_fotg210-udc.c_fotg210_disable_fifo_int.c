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
typedef  int /*<<< orphan*/  u32 ;
struct fotg210_ep {TYPE_1__* fotg210; scalar_t__ epnum; scalar_t__ dir_in; } ;
struct TYPE_2__ {scalar_t__ reg; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMISGR1_MF_IN_INT (scalar_t__) ; 
 int /*<<< orphan*/  DMISGR1_MF_OUTSPK_INT (scalar_t__) ; 
 scalar_t__ FOTG210_DMISGR1 ; 
 int /*<<< orphan*/  ioread32 (scalar_t__) ; 
 int /*<<< orphan*/  iowrite32 (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void fotg210_disable_fifo_int(struct fotg210_ep *ep)
{
	u32 value = ioread32(ep->fotg210->reg + FOTG210_DMISGR1);

	if (ep->dir_in)
		value |= DMISGR1_MF_IN_INT(ep->epnum - 1);
	else
		value |= DMISGR1_MF_OUTSPK_INT(ep->epnum - 1);
	iowrite32(value, ep->fotg210->reg + FOTG210_DMISGR1);
}