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
struct jme_adapter {int reg_pmcs; } ;

/* Variables and functions */
 int /*<<< orphan*/  JME_PMCS ; 
 int PMCS_STMASK ; 
 int /*<<< orphan*/  jwrite32 (struct jme_adapter*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static inline void
jme_clear_pm_enable_wol(struct jme_adapter *jme)
{
	jwrite32(jme, JME_PMCS, PMCS_STMASK | jme->reg_pmcs);
}