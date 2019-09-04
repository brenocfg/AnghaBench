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
typedef  int /*<<< orphan*/  u16 ;
struct reg_val {int member_1; int member_2; int member_3; int /*<<< orphan*/  const member_0; } ;
struct cphy {scalar_t__ priv; int /*<<< orphan*/ * phy_cache; } ;

/* Variables and functions */
 int /*<<< orphan*/  EDC_OPT_AEL2005 ; 
 int EDC_OPT_AEL2005_SIZE ; 
#define  MDIO_MMD_PMAPMD 128 
 scalar_t__ edc_sr ; 
 int /*<<< orphan*/  msleep (int) ; 
 int set_phy_regs (struct cphy*,struct reg_val const*) ; 
 int t3_get_edc_fw (struct cphy*,int /*<<< orphan*/ ,int) ; 
 int t3_mdio_write (struct cphy*,int /*<<< orphan*/  const,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ael2005_setup_sr_edc(struct cphy *phy)
{
	static const struct reg_val regs[] = {
		{ MDIO_MMD_PMAPMD, 0xc003, 0xffff, 0x181 },
		{ MDIO_MMD_PMAPMD, 0xc010, 0xffff, 0x448a },
		{ MDIO_MMD_PMAPMD, 0xc04a, 0xffff, 0x5200 },
		{ 0, 0, 0, 0 }
	};

	int i, err;

	err = set_phy_regs(phy, regs);
	if (err)
		return err;

	msleep(50);

	if (phy->priv != edc_sr)
		err = t3_get_edc_fw(phy, EDC_OPT_AEL2005,
				    EDC_OPT_AEL2005_SIZE);
	if (err)
		return err;

	for (i = 0; i <  EDC_OPT_AEL2005_SIZE / sizeof(u16) && !err; i += 2)
		err = t3_mdio_write(phy, MDIO_MMD_PMAPMD,
				    phy->phy_cache[i],
				    phy->phy_cache[i + 1]);
	if (!err)
		phy->priv = edc_sr;
	return err;
}