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
struct bcm_sysport_priv {int /*<<< orphan*/  is_lite; } ;

/* Variables and functions */
 int /*<<< orphan*/  INTRL2_CPU_CLEAR ; 
 int /*<<< orphan*/  intrl2_0_mask_set (struct bcm_sysport_priv*,int) ; 
 int /*<<< orphan*/  intrl2_0_writel (struct bcm_sysport_priv*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  intrl2_1_mask_set (struct bcm_sysport_priv*,int) ; 
 int /*<<< orphan*/  intrl2_1_writel (struct bcm_sysport_priv*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void bcm_sysport_mask_all_intrs(struct bcm_sysport_priv *priv)
{
	intrl2_0_mask_set(priv, 0xffffffff);
	intrl2_0_writel(priv, 0xffffffff, INTRL2_CPU_CLEAR);
	if (!priv->is_lite) {
		intrl2_1_mask_set(priv, 0xffffffff);
		intrl2_1_writel(priv, 0xffffffff, INTRL2_CPU_CLEAR);
	}
}