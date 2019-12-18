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
struct tsu_incr {int sub_ns; int ns; } ;
struct macb {int /*<<< orphan*/  tsu_clk_lock; } ;

/* Variables and functions */
 int GEM_BF (int /*<<< orphan*/ ,int) ; 
 int GEM_SUBNSINCRL_SIZE ; 
 int /*<<< orphan*/  NSINCR ; 
 int /*<<< orphan*/  SUBNSINCRH ; 
 int /*<<< orphan*/  SUBNSINCRL ; 
 int /*<<< orphan*/  TI ; 
 int /*<<< orphan*/  TISUBN ; 
 int /*<<< orphan*/  gem_writel (struct macb*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int gem_tsu_incr_set(struct macb *bp, struct tsu_incr *incr_spec)
{
	unsigned long flags;

	/* tsu_timer_incr register must be written after
	 * the tsu_timer_incr_sub_ns register and the write operation
	 * will cause the value written to the tsu_timer_incr_sub_ns register
	 * to take effect.
	 */
	spin_lock_irqsave(&bp->tsu_clk_lock, flags);
	/* RegBit[15:0] = Subns[23:8]; RegBit[31:24] = Subns[7:0] */
	gem_writel(bp, TISUBN, GEM_BF(SUBNSINCRL, incr_spec->sub_ns) |
		   GEM_BF(SUBNSINCRH, (incr_spec->sub_ns >>
			  GEM_SUBNSINCRL_SIZE)));
	gem_writel(bp, TI, GEM_BF(NSINCR, incr_spec->ns));
	spin_unlock_irqrestore(&bp->tsu_clk_lock, flags);

	return 0;
}