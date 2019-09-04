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
struct nb8800_priv {int dummy; } ;

/* Variables and functions */
 int nb8800_readl (struct nb8800_priv*,int) ; 
 int /*<<< orphan*/  nb8800_writel (struct nb8800_priv*,int,int) ; 

__attribute__((used)) static inline void nb8800_maskl(struct nb8800_priv *priv, int reg,
				u32 mask, u32 val)
{
	u32 old = nb8800_readl(priv, reg);
	u32 new = (old & ~mask) | (val & mask);

	if (new != old)
		nb8800_writel(priv, reg, new);
}