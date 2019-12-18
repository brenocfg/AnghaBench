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
struct ctlr_info {int interrupts_enabled; scalar_t__ vaddr; } ;

/* Variables and functions */
 int /*<<< orphan*/  SA5_PERF_INTR_OFF ; 
 scalar_t__ SA5_REPLY_INTR_MASK_OFFSET ; 
 int /*<<< orphan*/  readl (scalar_t__) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void SA5_performant_intr_mask(struct ctlr_info *h, unsigned long val)
{
	if (val) { /* turn on interrupts */
		h->interrupts_enabled = 1;
		writel(0, h->vaddr + SA5_REPLY_INTR_MASK_OFFSET);
		(void) readl(h->vaddr + SA5_REPLY_INTR_MASK_OFFSET);
	} else {
		h->interrupts_enabled = 0;
		writel(SA5_PERF_INTR_OFF,
			h->vaddr + SA5_REPLY_INTR_MASK_OFFSET);
		(void) readl(h->vaddr + SA5_REPLY_INTR_MASK_OFFSET);
	}
}