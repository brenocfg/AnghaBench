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
 int /*<<< orphan*/  intrl2_0_mask_set (struct bcm_sf2_priv*,int) ; 
 int /*<<< orphan*/  intrl2_0_writel (struct bcm_sf2_priv*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  intrl2_1_mask_set (struct bcm_sf2_priv*,int) ; 
 int /*<<< orphan*/  intrl2_1_writel (struct bcm_sf2_priv*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void bcm_sf2_intr_disable(struct bcm_sf2_priv *priv)
{
	intrl2_0_mask_set(priv, 0xffffffff);
	intrl2_0_writel(priv, 0xffffffff, INTRL2_CPU_CLEAR);
	intrl2_1_mask_set(priv, 0xffffffff);
	intrl2_1_writel(priv, 0xffffffff, INTRL2_CPU_CLEAR);
}