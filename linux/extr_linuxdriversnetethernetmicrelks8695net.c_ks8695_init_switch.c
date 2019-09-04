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
struct ks8695_priv {scalar_t__ phyiface_regs; } ;

/* Variables and functions */
 scalar_t__ KS8695_SEC0 ; 
 scalar_t__ KS8695_SEC1 ; 
 int LLED0S_LINK ; 
 int LLED1S_LINK_ACTIVITY ; 
 int SEC0_ENABLE ; 
 int SEC0_LLED0S ; 
 int SEC0_LLED1S ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static void
ks8695_init_switch(struct ks8695_priv *ksp)
{
	u32 ctrl;

	/* Default value for SEC0 according to datasheet */
	ctrl = 0x40819e00;

	/* LED0 = Speed	 LED1 = Link/Activity */
	ctrl &= ~(SEC0_LLED1S | SEC0_LLED0S);
	ctrl |= (LLED0S_LINK | LLED1S_LINK_ACTIVITY);

	/* Enable Switch */
	ctrl |= SEC0_ENABLE;

	writel(ctrl, ksp->phyiface_regs + KS8695_SEC0);

	/* Defaults for SEC1 */
	writel(0x9400100, ksp->phyiface_regs + KS8695_SEC1);
}