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
struct tg3 {int dummy; } ;

/* Variables and functions */
 int MII_TG3_FET_SHADOW_EN ; 
 int /*<<< orphan*/  MII_TG3_FET_SHDW_AUXSTAT2 ; 
 int MII_TG3_FET_SHDW_AUXSTAT2_APD ; 
 int /*<<< orphan*/  MII_TG3_FET_TEST ; 
 int /*<<< orphan*/  tg3_readphy (struct tg3*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  tg3_writephy (struct tg3*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void tg3_phy_fet_toggle_apd(struct tg3 *tp, bool enable)
{
	u32 phytest;

	if (!tg3_readphy(tp, MII_TG3_FET_TEST, &phytest)) {
		u32 phy;

		tg3_writephy(tp, MII_TG3_FET_TEST,
			     phytest | MII_TG3_FET_SHADOW_EN);
		if (!tg3_readphy(tp, MII_TG3_FET_SHDW_AUXSTAT2, &phy)) {
			if (enable)
				phy |= MII_TG3_FET_SHDW_AUXSTAT2_APD;
			else
				phy &= ~MII_TG3_FET_SHDW_AUXSTAT2_APD;
			tg3_writephy(tp, MII_TG3_FET_SHDW_AUXSTAT2, phy);
		}
		tg3_writephy(tp, MII_TG3_FET_TEST, phytest);
	}
}