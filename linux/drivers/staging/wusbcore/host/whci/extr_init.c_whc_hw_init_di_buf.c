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
struct whc {int n_devices; scalar_t__ base; int /*<<< orphan*/  di_buf_dma; TYPE_1__* di_buf; } ;
struct TYPE_2__ {int /*<<< orphan*/  addr_sec_info; } ;

/* Variables and functions */
 int /*<<< orphan*/  WHC_DI_DISABLE ; 
 scalar_t__ WUSBDEVICEINFOADDR ; 
 int /*<<< orphan*/  le_writeq (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void whc_hw_init_di_buf(struct whc *whc)
{
	int d;

	/* Disable all entries in the Device Information buffer. */
	for (d = 0; d < whc->n_devices; d++)
		whc->di_buf[d].addr_sec_info = WHC_DI_DISABLE;

	le_writeq(whc->di_buf_dma, whc->base + WUSBDEVICEINFOADDR);
}