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
struct cmac {TYPE_1__* instance; } ;
struct TYPE_2__ {int enabled; } ;

/* Variables and functions */
 int MAC_DIRECTION_RX ; 
 int MAC_DIRECTION_TX ; 
 int /*<<< orphan*/  RXXG_CONF1_VAL ; 
 int /*<<< orphan*/  SUNI1x10GEXP_REG_RXXG_CONFIG_1 ; 
 int /*<<< orphan*/  SUNI1x10GEXP_REG_TXXG_CONFIG_1 ; 
 int /*<<< orphan*/  TXXG_CONF1_VAL ; 
 int /*<<< orphan*/  pmwrite (struct cmac*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int pm3393_disable(struct cmac *cmac, int which)
{
	if (which & MAC_DIRECTION_RX)
		pmwrite(cmac, SUNI1x10GEXP_REG_RXXG_CONFIG_1, RXXG_CONF1_VAL);
	if (which & MAC_DIRECTION_TX)
		pmwrite(cmac, SUNI1x10GEXP_REG_TXXG_CONFIG_1, TXXG_CONF1_VAL);

	/*
	 * The disable is graceful. Give the PM3393 time.  Can't wait very
	 * long here, we may be holding locks.
	 */
	udelay(20);

	cmac->instance->enabled &= ~which;
	return 0;
}