#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct cfg80211_sched_scan_request {int n_channels; TYPE_1__** channels; } ;
struct brcmf_pno_config_le {int /*<<< orphan*/  channel_num; int /*<<< orphan*/ * channel_list; } ;
struct TYPE_2__ {int /*<<< orphan*/  hw_value; } ;

/* Variables and functions */
 int BRCMF_NUMCHANNELS ; 
 int ENOSPC ; 
 int /*<<< orphan*/  SCAN ; 
 int /*<<< orphan*/  brcmf_dbg (int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_to_le16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_to_le32 (int) ; 
 int le32_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int brcmf_pno_get_bucket_channels(struct cfg80211_sched_scan_request *r,
					 struct brcmf_pno_config_le *pno_cfg)
{
	u32 n_chan = le32_to_cpu(pno_cfg->channel_num);
	u16 chan;
	int i, err = 0;

	for (i = 0; i < r->n_channels; i++) {
		if (n_chan >= BRCMF_NUMCHANNELS) {
			err = -ENOSPC;
			goto done;
		}
		chan = r->channels[i]->hw_value;
		brcmf_dbg(SCAN, "[%d] Chan : %u\n", n_chan, chan);
		pno_cfg->channel_list[n_chan++] = cpu_to_le16(chan);
	}
	/* return number of channels */
	err = n_chan;
done:
	pno_cfg->channel_num = cpu_to_le32(n_chan);
	return err;
}