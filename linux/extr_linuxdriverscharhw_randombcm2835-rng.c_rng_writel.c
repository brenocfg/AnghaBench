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
struct bcm2835_rng_priv {scalar_t__ base; } ;

/* Variables and functions */
 int /*<<< orphan*/  CONFIG_CPU_BIG_ENDIAN ; 
 int /*<<< orphan*/  CONFIG_MIPS ; 
 scalar_t__ IS_ENABLED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __raw_writel (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  writel (scalar_t__,scalar_t__) ; 

__attribute__((used)) static inline void rng_writel(struct bcm2835_rng_priv *priv, u32 val,
			      u32 offset)
{
	if (IS_ENABLED(CONFIG_MIPS) && IS_ENABLED(CONFIG_CPU_BIG_ENDIAN))
		__raw_writel(val, priv->base + offset);
	else
		writel(val, priv->base + offset);
}