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
typedef  scalar_t__ u32 ;
struct jme_adapter {scalar_t__ reg_ghc; } ;

/* Variables and functions */
 scalar_t__ GHC_SPEED ; 
 scalar_t__ GHC_SPEED_1000M ; 
 int GHC_TO_CLK_GPHY ; 
 int GHC_TO_CLK_PCIE ; 
 int GHC_TXMAC_CLK_GPHY ; 
 int GHC_TXMAC_CLK_PCIE ; 
 int /*<<< orphan*/  JME_GHC ; 
 int /*<<< orphan*/  jwrite32f (struct jme_adapter*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static inline void
jme_mac_txclk_on(struct jme_adapter *jme)
{
	u32 speed = jme->reg_ghc & GHC_SPEED;
	if (speed == GHC_SPEED_1000M)
		jme->reg_ghc |= GHC_TO_CLK_GPHY | GHC_TXMAC_CLK_GPHY;
	else
		jme->reg_ghc |= GHC_TO_CLK_PCIE | GHC_TXMAC_CLK_PCIE;
	jwrite32f(jme, JME_GHC, jme->reg_ghc);
}