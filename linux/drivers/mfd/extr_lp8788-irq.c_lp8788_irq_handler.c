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
typedef  size_t u8 ;
struct lp8788_irq_data {int /*<<< orphan*/  domain; struct lp8788* lp; } ;
struct lp8788 {int dummy; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 int /*<<< orphan*/  LP8788_INT_1 ; 
 int LP8788_INT_MAX ; 
 int NUM_REGS ; 
 size_t _irq_to_addr (int) ; 
 size_t _irq_to_mask (int) ; 
 int /*<<< orphan*/  handle_nested_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  irq_find_mapping (int /*<<< orphan*/ ,int) ; 
 scalar_t__ lp8788_read_multi_bytes (struct lp8788*,int /*<<< orphan*/ ,size_t*,int) ; 

__attribute__((used)) static irqreturn_t lp8788_irq_handler(int irq, void *ptr)
{
	struct lp8788_irq_data *irqd = ptr;
	struct lp8788 *lp = irqd->lp;
	u8 status[NUM_REGS], addr, mask;
	bool handled = false;
	int i;

	if (lp8788_read_multi_bytes(lp, LP8788_INT_1, status, NUM_REGS))
		return IRQ_NONE;

	for (i = 0 ; i < LP8788_INT_MAX ; i++) {
		addr = _irq_to_addr(i);
		mask = _irq_to_mask(i);

		/* reporting only if the irq is enabled */
		if (status[addr] & mask) {
			handle_nested_irq(irq_find_mapping(irqd->domain, i));
			handled = true;
		}
	}

	return handled ? IRQ_HANDLED : IRQ_NONE;
}