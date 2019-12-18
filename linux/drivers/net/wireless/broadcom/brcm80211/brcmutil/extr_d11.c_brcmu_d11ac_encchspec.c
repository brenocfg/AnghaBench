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
struct brcmu_chan {scalar_t__ bw; scalar_t__ sb; scalar_t__ chnum; int /*<<< orphan*/  chspec; } ;

/* Variables and functions */
 scalar_t__ BRCMU_CHAN_BW_20 ; 
 scalar_t__ BRCMU_CHAN_SB_L ; 
 scalar_t__ BRCMU_CHAN_SB_NONE ; 
 int /*<<< orphan*/  BRCMU_CHSPEC_CH_MASK ; 
 int /*<<< orphan*/  BRCMU_CHSPEC_CH_SHIFT ; 
 int /*<<< orphan*/  BRCMU_CHSPEC_D11AC_BND_2G ; 
 int /*<<< orphan*/  BRCMU_CHSPEC_D11AC_BND_5G ; 
 int /*<<< orphan*/  BRCMU_CHSPEC_D11AC_BND_MASK ; 
 int /*<<< orphan*/  BRCMU_CHSPEC_D11AC_BW_MASK ; 
 int /*<<< orphan*/  BRCMU_CHSPEC_D11AC_SB_MASK ; 
 int /*<<< orphan*/  BRCMU_CHSPEC_D11AC_SB_SHIFT ; 
 scalar_t__ CH_MAX_2G_CHANNEL ; 
 int /*<<< orphan*/  brcmu_maskset16 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ d11ac_bw (scalar_t__) ; 

__attribute__((used)) static void brcmu_d11ac_encchspec(struct brcmu_chan *ch)
{
	if (ch->bw == BRCMU_CHAN_BW_20 || ch->sb == BRCMU_CHAN_SB_NONE)
		ch->sb = BRCMU_CHAN_SB_L;

	brcmu_maskset16(&ch->chspec, BRCMU_CHSPEC_CH_MASK,
			BRCMU_CHSPEC_CH_SHIFT, ch->chnum);
	brcmu_maskset16(&ch->chspec, BRCMU_CHSPEC_D11AC_SB_MASK,
			BRCMU_CHSPEC_D11AC_SB_SHIFT, ch->sb);
	brcmu_maskset16(&ch->chspec, BRCMU_CHSPEC_D11AC_BW_MASK,
			0, d11ac_bw(ch->bw));

	ch->chspec &= ~BRCMU_CHSPEC_D11AC_BND_MASK;
	if (ch->chnum <= CH_MAX_2G_CHANNEL)
		ch->chspec |= BRCMU_CHSPEC_D11AC_BND_2G;
	else
		ch->chspec |= BRCMU_CHSPEC_D11AC_BND_5G;
}