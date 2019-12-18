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
typedef  int u16 ;
struct fman_mac {int /*<<< orphan*/  tbiphy; int /*<<< orphan*/  dtsec_drv_param; } ;

/* Variables and functions */
 int BMCR_ANENABLE ; 
 int BMCR_ANRESTART ; 
 int BMCR_FULLDPLX ; 
 int BMCR_SPEED100 ; 
 int BMCR_SPEED1000 ; 
 int EINVAL ; 
 int /*<<< orphan*/  MII_BMCR ; 
 int /*<<< orphan*/  is_init_done (int /*<<< orphan*/ ) ; 
 int phy_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  phy_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

int dtsec_restart_autoneg(struct fman_mac *dtsec)
{
	u16 tmp_reg16;

	if (!is_init_done(dtsec->dtsec_drv_param))
		return -EINVAL;

	tmp_reg16 = phy_read(dtsec->tbiphy, MII_BMCR);

	tmp_reg16 &= ~(BMCR_SPEED100 | BMCR_SPEED1000);
	tmp_reg16 |= (BMCR_ANENABLE | BMCR_ANRESTART |
		      BMCR_FULLDPLX | BMCR_SPEED1000);

	phy_write(dtsec->tbiphy, MII_BMCR, tmp_reg16);

	return 0;
}