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
struct jme_adapter {int reg_ghc; } ;

/* Variables and functions */
 int GHC_TO_CLK_SRC ; 
 int GHC_TXMAC_CLK_SRC ; 
 int /*<<< orphan*/  JME_GHC ; 
 int /*<<< orphan*/  jwrite32f (struct jme_adapter*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static inline void
jme_mac_txclk_off(struct jme_adapter *jme)
{
	jme->reg_ghc &= ~(GHC_TO_CLK_SRC | GHC_TXMAC_CLK_SRC);
	jwrite32f(jme, JME_GHC, jme->reg_ghc);
}