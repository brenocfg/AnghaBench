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
struct fotg210_ep {TYPE_1__* fotg210; } ;
struct TYPE_2__ {scalar_t__ reg; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMATFNR_DISDMA ; 
 scalar_t__ FOTG210_DMATFNR ; 
 int /*<<< orphan*/  iowrite32 (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void fotg210_disable_dma(struct fotg210_ep *ep)
{
	iowrite32(DMATFNR_DISDMA, ep->fotg210->reg + FOTG210_DMATFNR);
}