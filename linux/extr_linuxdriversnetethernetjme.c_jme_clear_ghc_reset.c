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
struct jme_adapter {int /*<<< orphan*/  reg_ghc; } ;

/* Variables and functions */
 int /*<<< orphan*/  GHC_SWRST ; 
 int /*<<< orphan*/  JME_GHC ; 
 int /*<<< orphan*/  jwrite32f (struct jme_adapter*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void
jme_clear_ghc_reset(struct jme_adapter *jme)
{
	jme->reg_ghc &= ~GHC_SWRST;
	jwrite32f(jme, JME_GHC, jme->reg_ghc);
}