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
struct jme_adapter {int /*<<< orphan*/  reg_rxcs; } ;

/* Variables and functions */
 int /*<<< orphan*/  JME_RXCS ; 
 int JME_RX_DISABLE_TIMEOUT ; 
 int RXCS_ENABLE ; 
 int /*<<< orphan*/  jme_mac_rxclk_off (struct jme_adapter*) ; 
 int jread32 (struct jme_adapter*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jwrite32 (struct jme_adapter*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mdelay (int) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/  rmb () ; 
 int /*<<< orphan*/  wmb () ; 

__attribute__((used)) static inline void
jme_disable_rx_engine(struct jme_adapter *jme)
{
	int i;
	u32 val;

	/*
	 * Disable RX Engine
	 */
	jwrite32(jme, JME_RXCS, jme->reg_rxcs);
	wmb();

	val = jread32(jme, JME_RXCS);
	for (i = JME_RX_DISABLE_TIMEOUT ; (val & RXCS_ENABLE) && i > 0 ; --i) {
		mdelay(1);
		val = jread32(jme, JME_RXCS);
		rmb();
	}

	if (!i)
		pr_err("Disable RX engine timeout\n");

	/*
	 * Stop clock for RX MAC Processor
	 */
	jme_mac_rxclk_off(jme);
}