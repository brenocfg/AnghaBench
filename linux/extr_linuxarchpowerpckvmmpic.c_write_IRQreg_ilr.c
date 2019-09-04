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
typedef  int uint32_t ;
struct openpic {int flags; struct irq_source* src; } ;
struct irq_source {int output; int /*<<< orphan*/  idr; } ;

/* Variables and functions */
 int ILR_INTTGT_MASK ; 
 int OPENPIC_FLAG_ILR ; 
 int /*<<< orphan*/  pr_debug (char*,int,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static inline void write_IRQreg_ilr(struct openpic *opp, int n_IRQ,
				    uint32_t val)
{
	if (opp->flags & OPENPIC_FLAG_ILR) {
		struct irq_source *src = &opp->src[n_IRQ];

		src->output = val & ILR_INTTGT_MASK;
		pr_debug("Set ILR %d to 0x%08x, output %d\n", n_IRQ, src->idr,
			src->output);

		/* TODO: on MPIC v4.0 only, set nomask for non-INT */
	}
}