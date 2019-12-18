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
struct cas {int cas_flags; scalar_t__ regs; } ;

/* Variables and functions */
 int CAS_FLAG_REG_PLUS ; 
 int /*<<< orphan*/  INTRN_MASK_RX_EN ; 
 int /*<<< orphan*/  INTR_TX_DONE ; 
 scalar_t__ REG_INTR_MASK ; 
 scalar_t__ REG_PLUS_INTRN_MASK (int const) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void cas_enable_irq(struct cas *cp, const int ring)
{
	if (ring == 0) { /* all but TX_DONE */
		writel(INTR_TX_DONE, cp->regs + REG_INTR_MASK);
		return;
	}

	if (cp->cas_flags & CAS_FLAG_REG_PLUS) {
		switch (ring) {
#if defined (USE_PCI_INTB) || defined(USE_PCI_INTC) || defined(USE_PCI_INTD)
#ifdef USE_PCI_INTB
		case 1:
#endif
#ifdef USE_PCI_INTC
		case 2:
#endif
#ifdef USE_PCI_INTD
		case 3:
#endif
			writel(INTRN_MASK_RX_EN, cp->regs +
			       REG_PLUS_INTRN_MASK(ring));
			break;
#endif
		default:
			break;
		}
	}
}