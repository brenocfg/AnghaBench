#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u8 ;
typedef  int u32 ;
typedef  int u16 ;
struct TYPE_4__ {int full_duplex; int force_media; int advertising; scalar_t__ supports_gmii; } ;
struct TYPE_3__ {void* speed_duplex; } ;
struct r8152 {int /*<<< orphan*/  flags; TYPE_2__ mii; TYPE_1__ ups_info; } ;

/* Variables and functions */
 int ADVERTISE_1000FULL ; 
 int ADVERTISE_1000HALF ; 
 int ADVERTISE_100FULL ; 
 int ADVERTISE_100HALF ; 
 int ADVERTISE_10FULL ; 
 int ADVERTISE_10HALF ; 
 scalar_t__ AUTONEG_DISABLE ; 
 int BMCR_ANENABLE ; 
 int BMCR_ANRESTART ; 
 int BMCR_FULLDPLX ; 
 int BMCR_RESET ; 
 int BMCR_SPEED10 ; 
 int BMCR_SPEED100 ; 
 int BMCR_SPEED1000 ; 
 scalar_t__ DUPLEX_FULL ; 
 scalar_t__ DUPLEX_HALF ; 
 int EINVAL ; 
 void* FORCE_100M_FULL ; 
 void* FORCE_100M_HALF ; 
 void* FORCE_10M_FULL ; 
 void* FORCE_10M_HALF ; 
 int /*<<< orphan*/  MII_ADVERTISE ; 
 int /*<<< orphan*/  MII_BMCR ; 
 int /*<<< orphan*/  MII_CTRL1000 ; 
 void* NWAY_1000M_FULL ; 
 void* NWAY_100M_FULL ; 
 void* NWAY_100M_HALF ; 
 void* NWAY_10M_FULL ; 
 void* NWAY_10M_HALF ; 
 int /*<<< orphan*/  PHY_RESET ; 
 int RTL_ADVERTISED_1000_FULL ; 
 int RTL_ADVERTISED_100_FULL ; 
 int RTL_ADVERTISED_100_HALF ; 
 int RTL_ADVERTISED_10_FULL ; 
 int RTL_ADVERTISED_10_HALF ; 
#define  SPEED_10 130 
#define  SPEED_100 129 
#define  SPEED_1000 128 
 int /*<<< orphan*/  msleep (int) ; 
 int r8152_mdio_read (struct r8152*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  r8152_mdio_write (struct r8152*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ test_and_clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int rtl8152_set_speed(struct r8152 *tp, u8 autoneg, u32 speed, u8 duplex,
			     u32 advertising)
{
	u16 bmcr;
	int ret = 0;

	if (autoneg == AUTONEG_DISABLE) {
		if (duplex != DUPLEX_HALF && duplex != DUPLEX_FULL)
			return -EINVAL;

		switch (speed) {
		case SPEED_10:
			bmcr = BMCR_SPEED10;
			if (duplex == DUPLEX_FULL) {
				bmcr |= BMCR_FULLDPLX;
				tp->ups_info.speed_duplex = FORCE_10M_FULL;
			} else {
				tp->ups_info.speed_duplex = FORCE_10M_HALF;
			}
			break;
		case SPEED_100:
			bmcr = BMCR_SPEED100;
			if (duplex == DUPLEX_FULL) {
				bmcr |= BMCR_FULLDPLX;
				tp->ups_info.speed_duplex = FORCE_100M_FULL;
			} else {
				tp->ups_info.speed_duplex = FORCE_100M_HALF;
			}
			break;
		case SPEED_1000:
			if (tp->mii.supports_gmii) {
				bmcr = BMCR_SPEED1000 | BMCR_FULLDPLX;
				tp->ups_info.speed_duplex = NWAY_1000M_FULL;
				break;
			}
			/* fall through */
		default:
			ret = -EINVAL;
			goto out;
		}

		if (duplex == DUPLEX_FULL)
			tp->mii.full_duplex = 1;
		else
			tp->mii.full_duplex = 0;

		tp->mii.force_media = 1;
	} else {
		u16 anar, tmp1;
		u32 support;

		support = RTL_ADVERTISED_10_HALF | RTL_ADVERTISED_10_FULL |
			  RTL_ADVERTISED_100_HALF | RTL_ADVERTISED_100_FULL;

		if (tp->mii.supports_gmii)
			support |= RTL_ADVERTISED_1000_FULL;

		if (!(advertising & support))
			return -EINVAL;

		anar = r8152_mdio_read(tp, MII_ADVERTISE);
		tmp1 = anar & ~(ADVERTISE_10HALF | ADVERTISE_10FULL |
				ADVERTISE_100HALF | ADVERTISE_100FULL);
		if (advertising & RTL_ADVERTISED_10_HALF) {
			tmp1 |= ADVERTISE_10HALF;
			tp->ups_info.speed_duplex = NWAY_10M_HALF;
		}
		if (advertising & RTL_ADVERTISED_10_FULL) {
			tmp1 |= ADVERTISE_10FULL;
			tp->ups_info.speed_duplex = NWAY_10M_FULL;
		}

		if (advertising & RTL_ADVERTISED_100_HALF) {
			tmp1 |= ADVERTISE_100HALF;
			tp->ups_info.speed_duplex = NWAY_100M_HALF;
		}
		if (advertising & RTL_ADVERTISED_100_FULL) {
			tmp1 |= ADVERTISE_100FULL;
			tp->ups_info.speed_duplex = NWAY_100M_FULL;
		}

		if (anar != tmp1) {
			r8152_mdio_write(tp, MII_ADVERTISE, tmp1);
			tp->mii.advertising = tmp1;
		}

		if (tp->mii.supports_gmii) {
			u16 gbcr;

			gbcr = r8152_mdio_read(tp, MII_CTRL1000);
			tmp1 = gbcr & ~(ADVERTISE_1000FULL |
					ADVERTISE_1000HALF);

			if (advertising & RTL_ADVERTISED_1000_FULL) {
				tmp1 |= ADVERTISE_1000FULL;
				tp->ups_info.speed_duplex = NWAY_1000M_FULL;
			}

			if (gbcr != tmp1)
				r8152_mdio_write(tp, MII_CTRL1000, tmp1);
		}

		bmcr = BMCR_ANENABLE | BMCR_ANRESTART;

		tp->mii.force_media = 0;
	}

	if (test_and_clear_bit(PHY_RESET, &tp->flags))
		bmcr |= BMCR_RESET;

	r8152_mdio_write(tp, MII_BMCR, bmcr);

	if (bmcr & BMCR_RESET) {
		int i;

		for (i = 0; i < 50; i++) {
			msleep(20);
			if ((r8152_mdio_read(tp, MII_BMCR) & BMCR_RESET) == 0)
				break;
		}
	}

out:
	return ret;
}