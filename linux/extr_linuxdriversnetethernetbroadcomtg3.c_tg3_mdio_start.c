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
struct tg3 {int /*<<< orphan*/  mi_mode; } ;

/* Variables and functions */
 scalar_t__ ASIC_REV_5785 ; 
 int /*<<< orphan*/  MAC_MI_MODE ; 
 int /*<<< orphan*/  MAC_MI_MODE_AUTO_POLL ; 
 int /*<<< orphan*/  MDIOBUS_INITED ; 
 scalar_t__ tg3_asic_rev (struct tg3*) ; 
 scalar_t__ tg3_flag (struct tg3*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tg3_mdio_config_5785 (struct tg3*) ; 
 int /*<<< orphan*/  tw32_f (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static void tg3_mdio_start(struct tg3 *tp)
{
	tp->mi_mode &= ~MAC_MI_MODE_AUTO_POLL;
	tw32_f(MAC_MI_MODE, tp->mi_mode);
	udelay(80);

	if (tg3_flag(tp, MDIOBUS_INITED) &&
	    tg3_asic_rev(tp) == ASIC_REV_5785)
		tg3_mdio_config_5785(tp);
}