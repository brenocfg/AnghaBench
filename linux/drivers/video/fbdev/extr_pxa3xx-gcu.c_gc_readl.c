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
struct pxa3xx_gcu_priv {scalar_t__ mmio_base; } ;

/* Variables and functions */
 unsigned long __raw_readl (scalar_t__) ; 

__attribute__((used)) static inline unsigned long
gc_readl(struct pxa3xx_gcu_priv *priv, unsigned int off)
{
	return __raw_readl(priv->mmio_base + off);
}