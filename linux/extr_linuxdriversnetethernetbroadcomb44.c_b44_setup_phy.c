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
struct b44 {int flags; } ;

/* Variables and functions */
 int ADVERTISE_100FULL ; 
 int ADVERTISE_100HALF ; 
 int ADVERTISE_10FULL ; 
 int ADVERTISE_10HALF ; 
 int ADVERTISE_CSMA ; 
 int ADVERTISE_PAUSE_ASYM ; 
 int ADVERTISE_PAUSE_CAP ; 
 int B44_FLAG_100_BASE_T ; 
 int B44_FLAG_ADV_100FULL ; 
 int B44_FLAG_ADV_100HALF ; 
 int B44_FLAG_ADV_10FULL ; 
 int B44_FLAG_ADV_10HALF ; 
 int B44_FLAG_EXTERNAL_PHY ; 
 int B44_FLAG_FORCE_LINK ; 
 int B44_FLAG_FULL_DUPLEX ; 
 int B44_FLAG_PAUSE_AUTO ; 
 int /*<<< orphan*/  B44_MII_ALEDCTRL ; 
 int /*<<< orphan*/  B44_MII_TLEDCTRL ; 
 int BMCR_ANENABLE ; 
 int BMCR_ANRESTART ; 
 int BMCR_FULLDPLX ; 
 int BMCR_SPEED100 ; 
 int /*<<< orphan*/  MII_ADVERTISE ; 
 int MII_ALEDCTRL_ALLMSK ; 
 int /*<<< orphan*/  MII_BMCR ; 
 int MII_TLEDCTRL_ENABLE ; 
 int b44_readphy (struct b44*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  b44_set_flow_ctrl (struct b44*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  b44_wap54g10_workaround (struct b44*) ; 
 int b44_writephy (struct b44*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int b44_setup_phy(struct b44 *bp)
{
	u32 val;
	int err;

	b44_wap54g10_workaround(bp);

	if (bp->flags & B44_FLAG_EXTERNAL_PHY)
		return 0;
	if ((err = b44_readphy(bp, B44_MII_ALEDCTRL, &val)) != 0)
		goto out;
	if ((err = b44_writephy(bp, B44_MII_ALEDCTRL,
				val & MII_ALEDCTRL_ALLMSK)) != 0)
		goto out;
	if ((err = b44_readphy(bp, B44_MII_TLEDCTRL, &val)) != 0)
		goto out;
	if ((err = b44_writephy(bp, B44_MII_TLEDCTRL,
				val | MII_TLEDCTRL_ENABLE)) != 0)
		goto out;

	if (!(bp->flags & B44_FLAG_FORCE_LINK)) {
		u32 adv = ADVERTISE_CSMA;

		if (bp->flags & B44_FLAG_ADV_10HALF)
			adv |= ADVERTISE_10HALF;
		if (bp->flags & B44_FLAG_ADV_10FULL)
			adv |= ADVERTISE_10FULL;
		if (bp->flags & B44_FLAG_ADV_100HALF)
			adv |= ADVERTISE_100HALF;
		if (bp->flags & B44_FLAG_ADV_100FULL)
			adv |= ADVERTISE_100FULL;

		if (bp->flags & B44_FLAG_PAUSE_AUTO)
			adv |= ADVERTISE_PAUSE_CAP | ADVERTISE_PAUSE_ASYM;

		if ((err = b44_writephy(bp, MII_ADVERTISE, adv)) != 0)
			goto out;
		if ((err = b44_writephy(bp, MII_BMCR, (BMCR_ANENABLE |
						       BMCR_ANRESTART))) != 0)
			goto out;
	} else {
		u32 bmcr;

		if ((err = b44_readphy(bp, MII_BMCR, &bmcr)) != 0)
			goto out;
		bmcr &= ~(BMCR_FULLDPLX | BMCR_ANENABLE | BMCR_SPEED100);
		if (bp->flags & B44_FLAG_100_BASE_T)
			bmcr |= BMCR_SPEED100;
		if (bp->flags & B44_FLAG_FULL_DUPLEX)
			bmcr |= BMCR_FULLDPLX;
		if ((err = b44_writephy(bp, MII_BMCR, bmcr)) != 0)
			goto out;

		/* Since we will not be negotiating there is no safe way
		 * to determine if the link partner supports flow control
		 * or not.  So just disable it completely in this case.
		 */
		b44_set_flow_ctrl(bp, 0, 0);
	}

out:
	return err;
}