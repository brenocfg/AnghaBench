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
typedef  int /*<<< orphan*/  u16 ;
struct nphy_sfo_cfg {int dummy; } ;
struct chan_info_nphy_radio205x {int /*<<< orphan*/  PHY_BW1a; } ;
struct chan_info_nphy_radio2057_rev5 {int /*<<< orphan*/  PHY_BW1a; } ;
struct chan_info_nphy_radio2057 {int /*<<< orphan*/  PHY_BW1a; } ;
struct chan_info_nphy_2055 {int /*<<< orphan*/  PHY_BW1a; } ;
struct brcms_phy_pub {int dummy; } ;
struct TYPE_4__ {int radiorev; int /*<<< orphan*/  phy_rev; } ;
struct brcms_phy {scalar_t__ bw; TYPE_2__ pubpi; TYPE_1__* sh; } ;
struct TYPE_3__ {int /*<<< orphan*/  physhim; } ;

/* Variables and functions */
 int BPHY_BAND_SEL_UP20 ; 
 scalar_t__ CHSPEC_BW (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CHSPEC_CHANNEL (int /*<<< orphan*/ ) ; 
 scalar_t__ CHSPEC_IS40 (int /*<<< orphan*/ ) ; 
 scalar_t__ CHSPEC_IS5G (int /*<<< orphan*/ ) ; 
 scalar_t__ CHSPEC_SB_UPPER (int /*<<< orphan*/ ) ; 
 scalar_t__ NREV_GE (int /*<<< orphan*/ ,int) ; 
 int PRIM_SEL_UP20 ; 
 int RADIO_2055_MASTER_CNTRL1 ; 
 int RADIO_2056_SYN ; 
 int RADIO_2056_SYN_COM_CTRL ; 
 int RADIO_2057_TIA_CONFIG_CORE0 ; 
 int RADIO_2057_TIA_CONFIG_CORE1 ; 
 int /*<<< orphan*/  and_phy_reg (struct brcms_phy*,int,int) ; 
 int /*<<< orphan*/  mod_radio_reg (struct brcms_phy*,int,int,int) ; 
 int /*<<< orphan*/  or_phy_reg (struct brcms_phy*,int,int) ; 
 int /*<<< orphan*/  wlapi_bmac_bw_set (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  wlc_phy_chan2freq_nphy (struct brcms_phy*,int /*<<< orphan*/ ,int*,struct chan_info_nphy_radio2057 const**,struct chan_info_nphy_radio205x const**,struct chan_info_nphy_radio2057_rev5 const**,struct chan_info_nphy_2055 const**) ; 
 int /*<<< orphan*/  wlc_phy_chanspec_nphy_setup (struct brcms_phy*,int /*<<< orphan*/ ,struct nphy_sfo_cfg const*) ; 
 int /*<<< orphan*/  wlc_phy_chanspec_radio2055_setup (struct brcms_phy*,struct chan_info_nphy_2055 const*) ; 
 int /*<<< orphan*/  wlc_phy_chanspec_radio2056_setup (struct brcms_phy*,struct chan_info_nphy_radio205x const*) ; 
 int /*<<< orphan*/  wlc_phy_chanspec_radio2057_setup (struct brcms_phy*,struct chan_info_nphy_radio2057 const*,struct chan_info_nphy_radio2057_rev5 const*) ; 
 int /*<<< orphan*/  wlc_phy_chanspec_radio_set (struct brcms_phy_pub*,int /*<<< orphan*/ ) ; 

void wlc_phy_chanspec_set_nphy(struct brcms_phy *pi, u16 chanspec)
{
	int freq;
	const struct chan_info_nphy_radio2057 *t0 = NULL;
	const struct chan_info_nphy_radio205x *t1 = NULL;
	const struct chan_info_nphy_radio2057_rev5 *t2 = NULL;
	const struct chan_info_nphy_2055 *t3 = NULL;

	if (!wlc_phy_chan2freq_nphy
		    (pi, CHSPEC_CHANNEL(chanspec), &freq, &t0, &t1, &t2, &t3))
		return;

	wlc_phy_chanspec_radio_set((struct brcms_phy_pub *) pi, chanspec);

	if (CHSPEC_BW(chanspec) != pi->bw)
		wlapi_bmac_bw_set(pi->sh->physhim, CHSPEC_BW(chanspec));

	if (CHSPEC_IS40(chanspec)) {
		if (CHSPEC_SB_UPPER(chanspec)) {
			or_phy_reg(pi, 0xa0, BPHY_BAND_SEL_UP20);
			if (NREV_GE(pi->pubpi.phy_rev, 7))
				or_phy_reg(pi, 0x310, PRIM_SEL_UP20);
		} else {
			and_phy_reg(pi, 0xa0, ~BPHY_BAND_SEL_UP20);
			if (NREV_GE(pi->pubpi.phy_rev, 7))
				and_phy_reg(pi, 0x310,
					    (~PRIM_SEL_UP20 & 0xffff));
		}
	}

	if (NREV_GE(pi->pubpi.phy_rev, 3)) {
		if (NREV_GE(pi->pubpi.phy_rev, 7)) {

			if ((pi->pubpi.radiorev <= 4)
			    || (pi->pubpi.radiorev == 6)) {
				mod_radio_reg(pi, RADIO_2057_TIA_CONFIG_CORE0,
					      0x2,
					      (CHSPEC_IS5G(chanspec) ? (1 << 1)
					       : 0));
				mod_radio_reg(pi, RADIO_2057_TIA_CONFIG_CORE1,
					      0x2,
					      (CHSPEC_IS5G(chanspec) ? (1 << 1)
					       : 0));
			}

			wlc_phy_chanspec_radio2057_setup(pi, t0, t2);
			wlc_phy_chanspec_nphy_setup(pi, chanspec,
				(pi->pubpi.radiorev == 5) ?
				(const struct nphy_sfo_cfg *)&(t2->PHY_BW1a) :
				(const struct nphy_sfo_cfg *)&(t0->PHY_BW1a));

		} else {

			mod_radio_reg(pi,
				      RADIO_2056_SYN_COM_CTRL | RADIO_2056_SYN,
				      0x4,
				      (CHSPEC_IS5G(chanspec) ? (0x1 << 2) : 0));
			wlc_phy_chanspec_radio2056_setup(pi, t1);

			wlc_phy_chanspec_nphy_setup(pi, chanspec,
				(const struct nphy_sfo_cfg *) &(t1->PHY_BW1a));
		}

	} else {

		mod_radio_reg(pi, RADIO_2055_MASTER_CNTRL1, 0x70,
			      (CHSPEC_IS5G(chanspec) ? (0x02 << 4)
			       : (0x05 << 4)));

		wlc_phy_chanspec_radio2055_setup(pi, t3);
		wlc_phy_chanspec_nphy_setup(pi, chanspec,
					    (const struct nphy_sfo_cfg *)
					     &(t3->PHY_BW1a));
	}

}