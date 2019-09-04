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
struct bcm_sf2_priv {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  INTRL2_CPU_CLEAR ; 
 unsigned int P0_IRQ_OFF ; 
 unsigned int P7_IRQ_OFF ; 
 int /*<<< orphan*/  P_IRQ_MASK (unsigned int) ; 
 unsigned int P_IRQ_OFF (int) ; 
 int /*<<< orphan*/  intrl2_0_mask_set (struct bcm_sf2_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  intrl2_0_writel (struct bcm_sf2_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  intrl2_1_mask_set (struct bcm_sf2_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  intrl2_1_writel (struct bcm_sf2_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void bcm_sf2_port_intr_disable(struct bcm_sf2_priv *priv,
					     int port)
{
	unsigned int off;

	switch (port) {
	case 7:
		off = P7_IRQ_OFF;
		break;
	case 0:
		/* Port 0 interrupts are located on the first bank */
		intrl2_0_mask_set(priv, P_IRQ_MASK(P0_IRQ_OFF));
		intrl2_0_writel(priv, P_IRQ_MASK(P0_IRQ_OFF), INTRL2_CPU_CLEAR);
		return;
	default:
		off = P_IRQ_OFF(port);
		break;
	}

	intrl2_1_mask_set(priv, P_IRQ_MASK(off));
	intrl2_1_writel(priv, P_IRQ_MASK(off), INTRL2_CPU_CLEAR);
}