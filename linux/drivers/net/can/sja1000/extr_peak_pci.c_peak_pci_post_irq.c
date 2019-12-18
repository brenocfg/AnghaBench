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
typedef  int u16 ;
struct sja1000_priv {struct peak_pci_chan* priv; } ;
struct peak_pci_chan {int icr_mask; scalar_t__ cfg_base; } ;

/* Variables and functions */
 scalar_t__ PITA_ICR ; 
 int readw (scalar_t__) ; 
 int /*<<< orphan*/  writew (int,scalar_t__) ; 

__attribute__((used)) static void peak_pci_post_irq(const struct sja1000_priv *priv)
{
	struct peak_pci_chan *chan = priv->priv;
	u16 icr;

	/* Select and clear in PITA stored interrupt */
	icr = readw(chan->cfg_base + PITA_ICR);
	if (icr & chan->icr_mask)
		writew(chan->icr_mask, chan->cfg_base + PITA_ICR);
}