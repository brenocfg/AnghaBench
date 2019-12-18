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
typedef  size_t u32 ;
typedef  scalar_t__ u16 ;
struct brcmu_chan {scalar_t__ chspec; scalar_t__ chnum; int /*<<< orphan*/  bw; } ;
struct brcmf_pub {int dummy; } ;
struct brcmf_p2p_info {TYPE_2__* cfg; } ;
typedef  int /*<<< orphan*/  s32 ;
struct TYPE_3__ {int /*<<< orphan*/  (* encchspec ) (struct brcmu_chan*) ;} ;
struct TYPE_4__ {TYPE_1__ d11inf; struct brcmf_pub* pub; } ;

/* Variables and functions */
 size_t AF_PEER_SEARCH_CNT ; 
 int /*<<< orphan*/  BRCMU_CHAN_BW_20 ; 
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  P2PAPI_BSSCFG_DEVICE ; 
 scalar_t__ SOCIAL_CHAN_1 ; 
 scalar_t__ SOCIAL_CHAN_2 ; 
 scalar_t__ SOCIAL_CHAN_3 ; 
 size_t SOCIAL_CHAN_CNT ; 
 int /*<<< orphan*/  TRACE ; 
 int /*<<< orphan*/  WL_P2P_DISC_ST_SEARCH ; 
 int /*<<< orphan*/  bphy_err (struct brcmf_pub*,char*) ; 
 int /*<<< orphan*/  brcmf_dbg (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  brcmf_p2p_escan (struct brcmf_p2p_info*,size_t,scalar_t__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__* kcalloc (size_t,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (scalar_t__*) ; 
 int /*<<< orphan*/  stub1 (struct brcmu_chan*) ; 
 int /*<<< orphan*/  stub2 (struct brcmu_chan*) ; 
 int /*<<< orphan*/  stub3 (struct brcmu_chan*) ; 
 int /*<<< orphan*/  stub4 (struct brcmu_chan*) ; 

__attribute__((used)) static s32 brcmf_p2p_act_frm_search(struct brcmf_p2p_info *p2p, u16 channel)
{
	struct brcmf_pub *drvr = p2p->cfg->pub;
	s32 err;
	u32 channel_cnt;
	u16 *default_chan_list;
	u32 i;
	struct brcmu_chan ch;

	brcmf_dbg(TRACE, "Enter\n");

	if (channel)
		channel_cnt = AF_PEER_SEARCH_CNT;
	else
		channel_cnt = SOCIAL_CHAN_CNT;
	default_chan_list = kcalloc(channel_cnt, sizeof(*default_chan_list),
				    GFP_KERNEL);
	if (default_chan_list == NULL) {
		bphy_err(drvr, "channel list allocation failed\n");
		err = -ENOMEM;
		goto exit;
	}
	ch.bw = BRCMU_CHAN_BW_20;
	if (channel) {
		ch.chnum = channel;
		p2p->cfg->d11inf.encchspec(&ch);
		/* insert same channel to the chan_list */
		for (i = 0; i < channel_cnt; i++)
			default_chan_list[i] = ch.chspec;
	} else {
		ch.chnum = SOCIAL_CHAN_1;
		p2p->cfg->d11inf.encchspec(&ch);
		default_chan_list[0] = ch.chspec;
		ch.chnum = SOCIAL_CHAN_2;
		p2p->cfg->d11inf.encchspec(&ch);
		default_chan_list[1] = ch.chspec;
		ch.chnum = SOCIAL_CHAN_3;
		p2p->cfg->d11inf.encchspec(&ch);
		default_chan_list[2] = ch.chspec;
	}
	err = brcmf_p2p_escan(p2p, channel_cnt, default_chan_list,
			      WL_P2P_DISC_ST_SEARCH, P2PAPI_BSSCFG_DEVICE);
	kfree(default_chan_list);
exit:
	return err;
}