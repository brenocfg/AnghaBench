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
struct reg_val {int member_1; int member_2; int member_3; int /*<<< orphan*/  const member_0; } ;
struct cphy {int modtype; int /*<<< orphan*/  priv; } ;

/* Variables and functions */
#define  MDIO_MMD_PMAPMD 128 
 int /*<<< orphan*/  MDIO_PMA_LASI_CTRL ; 
 int ael2005_get_module_type (struct cphy*,int /*<<< orphan*/ ) ; 
 int ael2005_intr_enable (struct cphy*) ; 
 int ael2005_setup_sr_edc (struct cphy*) ; 
 int ael2005_setup_twinax_edc (struct cphy*,int) ; 
 int /*<<< orphan*/  edc_none ; 
 int /*<<< orphan*/  msleep (int) ; 
 int phy_modtype_twinax ; 
 int phy_modtype_twinax_long ; 
 int set_phy_regs (struct cphy*,struct reg_val const*) ; 
 int t3_mdio_read (struct cphy*,int /*<<< orphan*/  const,int /*<<< orphan*/ ,unsigned int*) ; 
 int t3_phy_reset (struct cphy*,int /*<<< orphan*/  const,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ael2005_reset(struct cphy *phy, int wait)
{
	static const struct reg_val regs0[] = {
		{ MDIO_MMD_PMAPMD, 0xc001, 0, 1 << 5 },
		{ MDIO_MMD_PMAPMD, 0xc017, 0, 1 << 5 },
		{ MDIO_MMD_PMAPMD, 0xc013, 0xffff, 0xf341 },
		{ MDIO_MMD_PMAPMD, 0xc210, 0xffff, 0x8000 },
		{ MDIO_MMD_PMAPMD, 0xc210, 0xffff, 0x8100 },
		{ MDIO_MMD_PMAPMD, 0xc210, 0xffff, 0x8000 },
		{ MDIO_MMD_PMAPMD, 0xc210, 0xffff, 0 },
		{ 0, 0, 0, 0 }
	};
	static const struct reg_val regs1[] = {
		{ MDIO_MMD_PMAPMD, 0xca00, 0xffff, 0x0080 },
		{ MDIO_MMD_PMAPMD, 0xca12, 0xffff, 0 },
		{ 0, 0, 0, 0 }
	};

	int err;
	unsigned int lasi_ctrl;

	err = t3_mdio_read(phy, MDIO_MMD_PMAPMD, MDIO_PMA_LASI_CTRL,
			   &lasi_ctrl);
	if (err)
		return err;

	err = t3_phy_reset(phy, MDIO_MMD_PMAPMD, 0);
	if (err)
		return err;

	msleep(125);
	phy->priv = edc_none;
	err = set_phy_regs(phy, regs0);
	if (err)
		return err;

	msleep(50);

	err = ael2005_get_module_type(phy, 0);
	if (err < 0)
		return err;
	phy->modtype = err;

	if (err == phy_modtype_twinax || err == phy_modtype_twinax_long)
		err = ael2005_setup_twinax_edc(phy, err);
	else
		err = ael2005_setup_sr_edc(phy);
	if (err)
		return err;

	err = set_phy_regs(phy, regs1);
	if (err)
		return err;

	/* reset wipes out interrupts, reenable them if they were on */
	if (lasi_ctrl & 1)
		err = ael2005_intr_enable(phy);
	return err;
}