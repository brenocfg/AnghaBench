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
struct mvs_info {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_APP_ERR_CONFIG ; 
 int /*<<< orphan*/  CMD_PHY_TIMER ; 
 int /*<<< orphan*/  CMD_SAS_CTL0 ; 
 int /*<<< orphan*/  CMD_SAS_CTL1 ; 
 int /*<<< orphan*/  CMD_WD_TIMER ; 
 int mvs_cr32 (struct mvs_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mvs_cw32 (struct mvs_info*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static inline void mvs_phy_hacks(struct mvs_info *mvi)
{
	u32 tmp;

	tmp = mvs_cr32(mvi, CMD_PHY_TIMER);
	tmp &= ~(1 << 9);
	tmp |= (1 << 10);
	mvs_cw32(mvi, CMD_PHY_TIMER, tmp);

	/* enable retry 127 times */
	mvs_cw32(mvi, CMD_SAS_CTL1, 0x7f7f);

	/* extend open frame timeout to max */
	tmp = mvs_cr32(mvi, CMD_SAS_CTL0);
	tmp &= ~0xffff;
	tmp |= 0x3fff;
	mvs_cw32(mvi, CMD_SAS_CTL0, tmp);

	mvs_cw32(mvi, CMD_WD_TIMER, 0x7a0000);

	/* not to halt for different port op during wideport link change */
	mvs_cw32(mvi, CMD_APP_ERR_CONFIG, 0xffefbf7d);
}