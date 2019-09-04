#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
typedef  size_t u16 ;
struct omap_rng_dev {TYPE_1__* pdata; scalar_t__ base; } ;
struct TYPE_2__ {scalar_t__* regs; } ;

/* Variables and functions */
 int /*<<< orphan*/  __raw_writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static inline void omap_rng_write(struct omap_rng_dev *priv, u16 reg,
				      u32 val)
{
	__raw_writel(val, priv->base + priv->pdata->regs[reg]);
}