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
typedef  int u8 ;
struct b53_device {int vlan_enabled; } ;

/* Variables and functions */
 int /*<<< orphan*/  B53_CTRL_PAGE ; 
 int /*<<< orphan*/  B53_SWITCH_MODE ; 
 int /*<<< orphan*/  B53_VLAN_CTRL0 ; 
 int /*<<< orphan*/  B53_VLAN_CTRL1 ; 
 int /*<<< orphan*/  B53_VLAN_CTRL3 ; 
 int /*<<< orphan*/  B53_VLAN_CTRL3_63XX ; 
 int /*<<< orphan*/  B53_VLAN_CTRL4 ; 
 int /*<<< orphan*/  B53_VLAN_CTRL4_25 ; 
 int /*<<< orphan*/  B53_VLAN_CTRL4_63XX ; 
 int /*<<< orphan*/  B53_VLAN_CTRL5 ; 
 int /*<<< orphan*/  B53_VLAN_CTRL5_25 ; 
 int /*<<< orphan*/  B53_VLAN_CTRL5_63XX ; 
 int /*<<< orphan*/  B53_VLAN_PAGE ; 
 int SM_SW_FWD_MODE ; 
 int VC0_RESERVED_1 ; 
 int VC0_VID_CHK_EN ; 
 int VC0_VID_HASH_VID ; 
 int VC0_VLAN_EN ; 
 int VC1_RX_MCST_FWD_EN ; 
 int VC1_RX_MCST_TAG_EN ; 
 int VC1_RX_MCST_UNTAG_EN ; 
 int VC3_HIGH_8BIT_EN ; 
 int VC4_ING_VID_CHECK_MASK ; 
 int VC4_ING_VID_CHECK_S ; 
 int VC4_ING_VID_VIO_DROP ; 
 int VC4_ING_VID_VIO_FWD ; 
 int VC4_ING_VID_VIO_TO_IMP ; 
 int VC5_DROP_VTABLE_MISS ; 
 int VC5_VID_FFF_EN ; 
 int /*<<< orphan*/  b53_read8 (struct b53_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  b53_write16 (struct b53_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  b53_write8 (struct b53_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ is5325 (struct b53_device*) ; 
 scalar_t__ is5365 (struct b53_device*) ; 
 scalar_t__ is63xx (struct b53_device*) ; 

__attribute__((used)) static void b53_enable_vlan(struct b53_device *dev, bool enable,
			    bool enable_filtering)
{
	u8 mgmt, vc0, vc1, vc4 = 0, vc5;

	b53_read8(dev, B53_CTRL_PAGE, B53_SWITCH_MODE, &mgmt);
	b53_read8(dev, B53_VLAN_PAGE, B53_VLAN_CTRL0, &vc0);
	b53_read8(dev, B53_VLAN_PAGE, B53_VLAN_CTRL1, &vc1);

	if (is5325(dev) || is5365(dev)) {
		b53_read8(dev, B53_VLAN_PAGE, B53_VLAN_CTRL4_25, &vc4);
		b53_read8(dev, B53_VLAN_PAGE, B53_VLAN_CTRL5_25, &vc5);
	} else if (is63xx(dev)) {
		b53_read8(dev, B53_VLAN_PAGE, B53_VLAN_CTRL4_63XX, &vc4);
		b53_read8(dev, B53_VLAN_PAGE, B53_VLAN_CTRL5_63XX, &vc5);
	} else {
		b53_read8(dev, B53_VLAN_PAGE, B53_VLAN_CTRL4, &vc4);
		b53_read8(dev, B53_VLAN_PAGE, B53_VLAN_CTRL5, &vc5);
	}

	mgmt &= ~SM_SW_FWD_MODE;

	if (enable) {
		vc0 |= VC0_VLAN_EN | VC0_VID_CHK_EN | VC0_VID_HASH_VID;
		vc1 |= VC1_RX_MCST_UNTAG_EN | VC1_RX_MCST_FWD_EN;
		vc4 &= ~VC4_ING_VID_CHECK_MASK;
		if (enable_filtering) {
			vc4 |= VC4_ING_VID_VIO_DROP << VC4_ING_VID_CHECK_S;
			vc5 |= VC5_DROP_VTABLE_MISS;
		} else {
			vc4 |= VC4_ING_VID_VIO_FWD << VC4_ING_VID_CHECK_S;
			vc5 &= ~VC5_DROP_VTABLE_MISS;
		}

		if (is5325(dev))
			vc0 &= ~VC0_RESERVED_1;

		if (is5325(dev) || is5365(dev))
			vc1 |= VC1_RX_MCST_TAG_EN;

	} else {
		vc0 &= ~(VC0_VLAN_EN | VC0_VID_CHK_EN | VC0_VID_HASH_VID);
		vc1 &= ~(VC1_RX_MCST_UNTAG_EN | VC1_RX_MCST_FWD_EN);
		vc4 &= ~VC4_ING_VID_CHECK_MASK;
		vc5 &= ~VC5_DROP_VTABLE_MISS;

		if (is5325(dev) || is5365(dev))
			vc4 |= VC4_ING_VID_VIO_FWD << VC4_ING_VID_CHECK_S;
		else
			vc4 |= VC4_ING_VID_VIO_TO_IMP << VC4_ING_VID_CHECK_S;

		if (is5325(dev) || is5365(dev))
			vc1 &= ~VC1_RX_MCST_TAG_EN;
	}

	if (!is5325(dev) && !is5365(dev))
		vc5 &= ~VC5_VID_FFF_EN;

	b53_write8(dev, B53_VLAN_PAGE, B53_VLAN_CTRL0, vc0);
	b53_write8(dev, B53_VLAN_PAGE, B53_VLAN_CTRL1, vc1);

	if (is5325(dev) || is5365(dev)) {
		/* enable the high 8 bit vid check on 5325 */
		if (is5325(dev) && enable)
			b53_write8(dev, B53_VLAN_PAGE, B53_VLAN_CTRL3,
				   VC3_HIGH_8BIT_EN);
		else
			b53_write8(dev, B53_VLAN_PAGE, B53_VLAN_CTRL3, 0);

		b53_write8(dev, B53_VLAN_PAGE, B53_VLAN_CTRL4_25, vc4);
		b53_write8(dev, B53_VLAN_PAGE, B53_VLAN_CTRL5_25, vc5);
	} else if (is63xx(dev)) {
		b53_write16(dev, B53_VLAN_PAGE, B53_VLAN_CTRL3_63XX, 0);
		b53_write8(dev, B53_VLAN_PAGE, B53_VLAN_CTRL4_63XX, vc4);
		b53_write8(dev, B53_VLAN_PAGE, B53_VLAN_CTRL5_63XX, vc5);
	} else {
		b53_write16(dev, B53_VLAN_PAGE, B53_VLAN_CTRL3, 0);
		b53_write8(dev, B53_VLAN_PAGE, B53_VLAN_CTRL4, vc4);
		b53_write8(dev, B53_VLAN_PAGE, B53_VLAN_CTRL5, vc5);
	}

	b53_write8(dev, B53_CTRL_PAGE, B53_SWITCH_MODE, mgmt);

	dev->vlan_enabled = enable;
}