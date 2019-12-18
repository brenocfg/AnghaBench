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
typedef  int /*<<< orphan*/  u32 ;
typedef  int u16 ;
struct velocity_info {int mii_status; int /*<<< orphan*/  mac_regs; int /*<<< orphan*/  phy_id; } ;

/* Variables and functions */
 int ADVERTISE_PAUSE_ASYM ; 
 int ADVERTISE_PAUSE_CAP ; 
 int BMCR_ISOLATE ; 
 int /*<<< orphan*/  MII_ADVERTISE ; 
 int /*<<< orphan*/  MII_BMCR ; 
 int /*<<< orphan*/  MII_REG_BITS_OFF (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MII_REG_BITS_ON (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MII_REG_PSCR ; 
 int /*<<< orphan*/  MII_SREVISION ; 
 int /*<<< orphan*/  MII_TPISTATUS ; 
#define  PHYID_CICADA_CS8201 133 
 int PHYID_GET_PHY_ID (int /*<<< orphan*/ ) ; 
#define  PHYID_ICPLUS_IP101A 132 
#define  PHYID_MARVELL_1000 131 
#define  PHYID_MARVELL_1000S 130 
#define  PHYID_VT3216_32BIT 129 
#define  PHYID_VT3216_64BIT 128 
 int PLED_LALBE ; 
 int PSCR_ACRSTX ; 
 int TCSR_ECHODIS ; 
 int VELOCITY_DUPLEX_FULL ; 
 int /*<<< orphan*/  velocity_mii_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  velocity_mii_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void mii_init(struct velocity_info *vptr, u32 mii_status)
{
	u16 BMCR;

	switch (PHYID_GET_PHY_ID(vptr->phy_id)) {
	case PHYID_ICPLUS_IP101A:
		MII_REG_BITS_ON((ADVERTISE_PAUSE_ASYM | ADVERTISE_PAUSE_CAP),
						MII_ADVERTISE, vptr->mac_regs);
		if (vptr->mii_status & VELOCITY_DUPLEX_FULL)
			MII_REG_BITS_ON(TCSR_ECHODIS, MII_SREVISION,
								vptr->mac_regs);
		else
			MII_REG_BITS_OFF(TCSR_ECHODIS, MII_SREVISION,
								vptr->mac_regs);
		MII_REG_BITS_ON(PLED_LALBE, MII_TPISTATUS, vptr->mac_regs);
		break;
	case PHYID_CICADA_CS8201:
		/*
		 *	Reset to hardware default
		 */
		MII_REG_BITS_OFF((ADVERTISE_PAUSE_ASYM | ADVERTISE_PAUSE_CAP), MII_ADVERTISE, vptr->mac_regs);
		/*
		 *	Turn on ECHODIS bit in NWay-forced full mode and turn it
		 *	off it in NWay-forced half mode for NWay-forced v.s.
		 *	legacy-forced issue.
		 */
		if (vptr->mii_status & VELOCITY_DUPLEX_FULL)
			MII_REG_BITS_ON(TCSR_ECHODIS, MII_SREVISION, vptr->mac_regs);
		else
			MII_REG_BITS_OFF(TCSR_ECHODIS, MII_SREVISION, vptr->mac_regs);
		/*
		 *	Turn on Link/Activity LED enable bit for CIS8201
		 */
		MII_REG_BITS_ON(PLED_LALBE, MII_TPISTATUS, vptr->mac_regs);
		break;
	case PHYID_VT3216_32BIT:
	case PHYID_VT3216_64BIT:
		/*
		 *	Reset to hardware default
		 */
		MII_REG_BITS_ON((ADVERTISE_PAUSE_ASYM | ADVERTISE_PAUSE_CAP), MII_ADVERTISE, vptr->mac_regs);
		/*
		 *	Turn on ECHODIS bit in NWay-forced full mode and turn it
		 *	off it in NWay-forced half mode for NWay-forced v.s.
		 *	legacy-forced issue
		 */
		if (vptr->mii_status & VELOCITY_DUPLEX_FULL)
			MII_REG_BITS_ON(TCSR_ECHODIS, MII_SREVISION, vptr->mac_regs);
		else
			MII_REG_BITS_OFF(TCSR_ECHODIS, MII_SREVISION, vptr->mac_regs);
		break;

	case PHYID_MARVELL_1000:
	case PHYID_MARVELL_1000S:
		/*
		 *	Assert CRS on Transmit
		 */
		MII_REG_BITS_ON(PSCR_ACRSTX, MII_REG_PSCR, vptr->mac_regs);
		/*
		 *	Reset to hardware default
		 */
		MII_REG_BITS_ON((ADVERTISE_PAUSE_ASYM | ADVERTISE_PAUSE_CAP), MII_ADVERTISE, vptr->mac_regs);
		break;
	default:
		;
	}
	velocity_mii_read(vptr->mac_regs, MII_BMCR, &BMCR);
	if (BMCR & BMCR_ISOLATE) {
		BMCR &= ~BMCR_ISOLATE;
		velocity_mii_write(vptr->mac_regs, MII_BMCR, BMCR);
	}
}