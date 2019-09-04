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
struct s3c24xx_dclk {int /*<<< orphan*/  dclk_lock; int /*<<< orphan*/  base; } ;

/* Variables and functions */
 int DCLKCON_DCLK_DIV_MASK ; 
 int readl_relaxed (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  writel_relaxed (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void s3c24xx_dclk_update_cmp(struct s3c24xx_dclk *s3c24xx_dclk,
				    int div_shift, int cmp_shift)
{
	unsigned long flags = 0;
	u32 dclk_con, div, cmp;

	spin_lock_irqsave(&s3c24xx_dclk->dclk_lock, flags);

	dclk_con = readl_relaxed(s3c24xx_dclk->base);

	div = ((dclk_con >> div_shift) & DCLKCON_DCLK_DIV_MASK) + 1;
	cmp = ((div + 1) / 2) - 1;

	dclk_con &= ~(DCLKCON_DCLK_DIV_MASK << cmp_shift);
	dclk_con |= (cmp << cmp_shift);

	writel_relaxed(dclk_con, s3c24xx_dclk->base);

	spin_unlock_irqrestore(&s3c24xx_dclk->dclk_lock, flags);
}