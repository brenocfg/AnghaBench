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
struct net_device {int dummy; } ;
struct cas_rx_comp {int dummy; } ;
struct cas {int* rx_cur; int* rx_new; int cas_flags; scalar_t__ regs; struct cas_rx_comp** init_rxcs; } ;

/* Variables and functions */
 int CAS_FLAG_REG_PLUS ; 
 int /*<<< orphan*/  KERN_DEBUG ; 
 scalar_t__ REG_PLUS_RX_COMPN_TAIL (int) ; 
 scalar_t__ REG_RX_COMP_HEAD ; 
 scalar_t__ REG_RX_COMP_TAIL ; 
 int RX_COMP_ENTRY (int,int) ; 
 int /*<<< orphan*/  cas_rxc_init (struct cas_rx_comp*) ; 
 int /*<<< orphan*/  intr ; 
 int /*<<< orphan*/  netif_printk (struct cas*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct net_device*,char*,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  readl (scalar_t__) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static void cas_post_rxcs_ringN(struct net_device *dev,
				struct cas *cp, int ring)
{
	struct cas_rx_comp *rxc = cp->init_rxcs[ring];
	int last, entry;

	last = cp->rx_cur[ring];
	entry = cp->rx_new[ring];
	netif_printk(cp, intr, KERN_DEBUG, dev,
		     "rxc[%d] interrupt, done: %d/%d\n",
		     ring, readl(cp->regs + REG_RX_COMP_HEAD), entry);

	/* zero and re-mark descriptors */
	while (last != entry) {
		cas_rxc_init(rxc + last);
		last = RX_COMP_ENTRY(ring, last + 1);
	}
	cp->rx_cur[ring] = last;

	if (ring == 0)
		writel(last, cp->regs + REG_RX_COMP_TAIL);
	else if (cp->cas_flags & CAS_FLAG_REG_PLUS)
		writel(last, cp->regs + REG_PLUS_RX_COMPN_TAIL(ring));
}