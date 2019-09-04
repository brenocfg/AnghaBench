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
 int MII_TG3_AUXCTL_ACTL_SMDSP_ENA ; 
 int MII_TG3_AUXCTL_ACTL_TX_6DB ; 
 int /*<<< orphan*/  MII_TG3_AUXCTL_SHDWSEL_AUXCTL ; 
 int tg3_phy_auxctl_read (struct tg3*,int /*<<< orphan*/ ,int*) ; 
 int tg3_phy_auxctl_write (struct tg3*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int tg3_phy_toggle_auxctl_smdsp(struct tg3 *tp, bool enable)
{
	u32 val;
	int err;

	err = tg3_phy_auxctl_read(tp, MII_TG3_AUXCTL_SHDWSEL_AUXCTL, &val);

	if (err)
		return err;

	if (enable)
		val |= MII_TG3_AUXCTL_ACTL_SMDSP_ENA;
	else
		val &= ~MII_TG3_AUXCTL_ACTL_SMDSP_ENA;

	err = tg3_phy_auxctl_write((tp), MII_TG3_AUXCTL_SHDWSEL_AUXCTL,
				   val | MII_TG3_AUXCTL_ACTL_TX_6DB);

	return err;
}