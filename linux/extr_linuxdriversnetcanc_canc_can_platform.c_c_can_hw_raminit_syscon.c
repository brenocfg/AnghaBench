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
typedef  int u32 ;
struct TYPE_2__ {int start; int done; } ;
struct c_can_raminit {TYPE_1__ bits; int /*<<< orphan*/  reg; int /*<<< orphan*/  syscon; scalar_t__ needs_pulse; } ;
struct c_can_priv {struct c_can_raminit raminit_sys; } ;

/* Variables and functions */
 int /*<<< orphan*/  c_can_hw_raminit_wait_syscon (struct c_can_priv const*,int,int) ; 
 int /*<<< orphan*/  raminit_lock ; 
 int /*<<< orphan*/  regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void c_can_hw_raminit_syscon(const struct c_can_priv *priv, bool enable)
{
	const struct c_can_raminit *raminit = &priv->raminit_sys;
	u32 ctrl = 0;
	u32 mask;

	spin_lock(&raminit_lock);

	mask = 1 << raminit->bits.start | 1 << raminit->bits.done;
	regmap_read(raminit->syscon, raminit->reg, &ctrl);

	/* We clear the start bit first. The start bit is
	 * looking at the 0 -> transition, but is not self clearing;
	 * NOTE: DONE must be written with 1 to clear it.
	 * We can't clear the DONE bit here using regmap_update_bits()
	 * as it will bypass the write if initial condition is START:0 DONE:1
	 * e.g. on DRA7 which needs START pulse.
	 */
	ctrl &= ~mask;	/* START = 0, DONE = 0 */
	regmap_update_bits(raminit->syscon, raminit->reg, mask, ctrl);

	/* check if START bit is 0. Ignore DONE bit for now
	 * as it can be either 0 or 1.
	 */
	c_can_hw_raminit_wait_syscon(priv, 1 << raminit->bits.start, ctrl);

	if (enable) {
		/* Clear DONE bit & set START bit. */
		ctrl |= 1 << raminit->bits.start;
		/* DONE must be written with 1 to clear it */
		ctrl |= 1 << raminit->bits.done;
		regmap_update_bits(raminit->syscon, raminit->reg, mask, ctrl);
		/* prevent further clearing of DONE bit */
		ctrl &= ~(1 << raminit->bits.done);
		/* clear START bit if start pulse is needed */
		if (raminit->needs_pulse) {
			ctrl &= ~(1 << raminit->bits.start);
			regmap_update_bits(raminit->syscon, raminit->reg,
					   mask, ctrl);
		}

		ctrl |= 1 << raminit->bits.done;
		c_can_hw_raminit_wait_syscon(priv, mask, ctrl);
	}
	spin_unlock(&raminit_lock);
}