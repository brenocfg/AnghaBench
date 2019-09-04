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
struct gdsc {int /*<<< orphan*/  clamp_io_ctrl; int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  GMEM_RESET_MASK ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static inline void gdsc_assert_reset_aon(struct gdsc *sc)
{
	regmap_update_bits(sc->regmap, sc->clamp_io_ctrl,
			   GMEM_RESET_MASK, 1);
	udelay(1);
	regmap_update_bits(sc->regmap, sc->clamp_io_ctrl,
			   GMEM_RESET_MASK, 0);
}