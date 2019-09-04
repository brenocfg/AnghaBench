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
struct bcmgenet_priv {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  INTRL2_CPU_CLEAR ; 
 int /*<<< orphan*/  INTRL2_CPU_MASK_SET ; 
 int /*<<< orphan*/  bcmgenet_intrl2_0_writel (struct bcmgenet_priv*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bcmgenet_intrl2_1_writel (struct bcmgenet_priv*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void bcmgenet_intr_disable(struct bcmgenet_priv *priv)
{
	/* Mask all interrupts.*/
	bcmgenet_intrl2_0_writel(priv, 0xFFFFFFFF, INTRL2_CPU_MASK_SET);
	bcmgenet_intrl2_0_writel(priv, 0xFFFFFFFF, INTRL2_CPU_CLEAR);
	bcmgenet_intrl2_1_writel(priv, 0xFFFFFFFF, INTRL2_CPU_MASK_SET);
	bcmgenet_intrl2_1_writel(priv, 0xFFFFFFFF, INTRL2_CPU_CLEAR);
}