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
typedef  scalar_t__ u8 ;
typedef  int u16 ;
struct brcmu_chan {int chspec; int /*<<< orphan*/  band; scalar_t__ control_ch_num; int /*<<< orphan*/  sb; int /*<<< orphan*/  bw; scalar_t__ chnum; } ;

/* Variables and functions */
 int /*<<< orphan*/  BRCMU_CHAN_BAND_2G ; 
 int /*<<< orphan*/  BRCMU_CHAN_BAND_5G ; 
 int /*<<< orphan*/  BRCMU_CHAN_BW_20 ; 
 int /*<<< orphan*/  BRCMU_CHAN_BW_40 ; 
 int /*<<< orphan*/  BRCMU_CHAN_SB_L ; 
 int /*<<< orphan*/  BRCMU_CHAN_SB_NONE ; 
 int /*<<< orphan*/  BRCMU_CHAN_SB_U ; 
 int BRCMU_CHSPEC_CH_MASK ; 
#define  BRCMU_CHSPEC_D11N_BND_2G 131 
#define  BRCMU_CHSPEC_D11N_BND_5G 130 
 int BRCMU_CHSPEC_D11N_BND_MASK ; 
#define  BRCMU_CHSPEC_D11N_BW_20 129 
#define  BRCMU_CHSPEC_D11N_BW_40 128 
 int BRCMU_CHSPEC_D11N_BW_MASK ; 
 int BRCMU_CHSPEC_D11N_SB_L ; 
 int BRCMU_CHSPEC_D11N_SB_MASK ; 
 int /*<<< orphan*/  CH_10MHZ_APART ; 
 int /*<<< orphan*/  WARN_ONCE (int,char*,int) ; 

__attribute__((used)) static void brcmu_d11n_decchspec(struct brcmu_chan *ch)
{
	u16 val;

	ch->chnum = (u8)(ch->chspec & BRCMU_CHSPEC_CH_MASK);
	ch->control_ch_num = ch->chnum;

	switch (ch->chspec & BRCMU_CHSPEC_D11N_BW_MASK) {
	case BRCMU_CHSPEC_D11N_BW_20:
		ch->bw = BRCMU_CHAN_BW_20;
		ch->sb = BRCMU_CHAN_SB_NONE;
		break;
	case BRCMU_CHSPEC_D11N_BW_40:
		ch->bw = BRCMU_CHAN_BW_40;
		val = ch->chspec & BRCMU_CHSPEC_D11N_SB_MASK;
		if (val == BRCMU_CHSPEC_D11N_SB_L) {
			ch->sb = BRCMU_CHAN_SB_L;
			ch->control_ch_num -= CH_10MHZ_APART;
		} else {
			ch->sb = BRCMU_CHAN_SB_U;
			ch->control_ch_num += CH_10MHZ_APART;
		}
		break;
	default:
		WARN_ONCE(1, "Invalid chanspec 0x%04x\n", ch->chspec);
		break;
	}

	switch (ch->chspec & BRCMU_CHSPEC_D11N_BND_MASK) {
	case BRCMU_CHSPEC_D11N_BND_5G:
		ch->band = BRCMU_CHAN_BAND_5G;
		break;
	case BRCMU_CHSPEC_D11N_BND_2G:
		ch->band = BRCMU_CHAN_BAND_2G;
		break;
	default:
		WARN_ONCE(1, "Invalid chanspec 0x%04x\n", ch->chspec);
		break;
	}
}