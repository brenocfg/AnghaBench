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
typedef  int u16 ;
struct fixed_phy_status {scalar_t__ asym_pause; scalar_t__ pause; scalar_t__ link; scalar_t__ duplex; int /*<<< orphan*/  speed; } ;
struct TYPE_4__ {int bmsr; int estat; int lpa; int lpagb; } ;
struct TYPE_3__ {int bmsr; int estat; int lpa; int lpagb; } ;

/* Variables and functions */
 int BMCR_ANENABLE ; 
 int BMSR_ANEGCAPABLE ; 
 int BMSR_ANEGCOMPLETE ; 
 int BMSR_LSTATUS ; 
 int LPA_PAUSE_ASYM ; 
 int LPA_PAUSE_CAP ; 
#define  MII_BMCR 136 
#define  MII_BMSR 135 
#define  MII_ESTATUS 134 
#define  MII_LPA 133 
#define  MII_MMD_CTRL 132 
#define  MII_MMD_DATA 131 
#define  MII_PHYSID1 130 
#define  MII_PHYSID2 129 
 int MII_REGS_NUM ; 
#define  MII_STAT1000 128 
 int SWMII_DUPLEX_FULL ; 
 int SWMII_DUPLEX_HALF ; 
 scalar_t__ WARN_ON (int) ; 
 TYPE_2__* duplex ; 
 TYPE_1__* speed ; 
 int swphy_decode_speed (int /*<<< orphan*/ ) ; 

int swphy_read_reg(int reg, const struct fixed_phy_status *state)
{
	int speed_index, duplex_index;
	u16 bmsr = BMSR_ANEGCAPABLE;
	u16 estat = 0;
	u16 lpagb = 0;
	u16 lpa = 0;

	if (reg > MII_REGS_NUM)
		return -1;

	speed_index = swphy_decode_speed(state->speed);
	if (WARN_ON(speed_index < 0))
		return 0;

	duplex_index = state->duplex ? SWMII_DUPLEX_FULL : SWMII_DUPLEX_HALF;

	bmsr |= speed[speed_index].bmsr & duplex[duplex_index].bmsr;
	estat |= speed[speed_index].estat & duplex[duplex_index].estat;

	if (state->link) {
		bmsr |= BMSR_LSTATUS | BMSR_ANEGCOMPLETE;

		lpa   |= speed[speed_index].lpa   & duplex[duplex_index].lpa;
		lpagb |= speed[speed_index].lpagb & duplex[duplex_index].lpagb;

		if (state->pause)
			lpa |= LPA_PAUSE_CAP;

		if (state->asym_pause)
			lpa |= LPA_PAUSE_ASYM;
	}

	switch (reg) {
	case MII_BMCR:
		return BMCR_ANENABLE;
	case MII_BMSR:
		return bmsr;
	case MII_PHYSID1:
	case MII_PHYSID2:
		return 0;
	case MII_LPA:
		return lpa;
	case MII_STAT1000:
		return lpagb;
	case MII_ESTATUS:
		return estat;

	/*
	 * We do not support emulating Clause 45 over Clause 22 register
	 * reads.  Return an error instead of bogus data.
	 */
	case MII_MMD_CTRL:
	case MII_MMD_DATA:
		return -1;

	default:
		return 0xffff;
	}
}