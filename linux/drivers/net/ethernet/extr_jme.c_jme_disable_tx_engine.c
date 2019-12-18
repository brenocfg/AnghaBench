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
struct jme_adapter {int reg_txcs; } ;

/* Variables and functions */
 int /*<<< orphan*/  JME_TXCS ; 
 int JME_TX_DISABLE_TIMEOUT ; 
 int TXCS_ENABLE ; 
 int TXCS_SELECT_QUEUE0 ; 
 int /*<<< orphan*/  jme_mac_txclk_off (struct jme_adapter*) ; 
 int jread32 (struct jme_adapter*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jwrite32 (struct jme_adapter*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mdelay (int) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/  rmb () ; 
 int /*<<< orphan*/  wmb () ; 

__attribute__((used)) static inline void
jme_disable_tx_engine(struct jme_adapter *jme)
{
	int i;
	u32 val;

	/*
	 * Disable TX Engine
	 */
	jwrite32(jme, JME_TXCS, jme->reg_txcs | TXCS_SELECT_QUEUE0);
	wmb();

	val = jread32(jme, JME_TXCS);
	for (i = JME_TX_DISABLE_TIMEOUT ; (val & TXCS_ENABLE) && i > 0 ; --i) {
		mdelay(1);
		val = jread32(jme, JME_TXCS);
		rmb();
	}

	if (!i)
		pr_err("Disable TX engine timeout\n");

	/*
	 * Stop clock for TX MAC Processor
	 */
	jme_mac_txclk_off(jme);
}