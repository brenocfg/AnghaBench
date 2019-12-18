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
struct bm_portal {int dummy; } ;
struct bman_portal {int irq_sources; struct bm_portal p; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  BM_REG_ISR ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 int bm_in (struct bm_portal*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bm_out (struct bm_portal*,int /*<<< orphan*/ ,int) ; 
 int poll_portal_slow (struct bman_portal*,int) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static irqreturn_t portal_isr(int irq, void *ptr)
{
	struct bman_portal *p = ptr;
	struct bm_portal *portal = &p->p;
	u32 clear = p->irq_sources;
	u32 is = bm_in(portal, BM_REG_ISR) & p->irq_sources;

	if (unlikely(!is))
		return IRQ_NONE;

	clear |= poll_portal_slow(p, is);
	bm_out(portal, BM_REG_ISR, clear);
	return IRQ_HANDLED;
}