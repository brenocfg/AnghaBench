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
struct jme_adapter {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  JME_APMC ; 
 int JME_APMC_PSEUDO_HP_EN ; 
 int jread32 (struct jme_adapter*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int
jme_pseudo_hotplug_enabled(struct jme_adapter *jme)
{
	u32 apmc;
	apmc = jread32(jme, JME_APMC);
	return apmc & JME_APMC_PSEUDO_HP_EN;
}