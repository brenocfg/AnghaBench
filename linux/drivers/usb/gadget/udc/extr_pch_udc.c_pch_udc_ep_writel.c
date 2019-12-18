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
struct pch_udc_ep {scalar_t__ offset_addr; TYPE_1__* dev; } ;
struct TYPE_2__ {scalar_t__ base_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  iowrite32 (unsigned long,scalar_t__) ; 

__attribute__((used)) static inline void pch_udc_ep_writel(struct pch_udc_ep *ep,
				    unsigned long val, unsigned long reg)
{
	iowrite32(val, ep->dev->base_addr + ep->offset_addr + reg);
}