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
struct cfg80211_sched_scan_request {TYPE_1__* scan_plans; } ;
struct brcmf_pno_info {int n_reqs; struct cfg80211_sched_scan_request** reqs; } ;
struct brcmf_pno_config_le {int dummy; } ;
struct brcmf_gscan_bucket_config {int bucket_end_index; int bucket_freq_multiple; int /*<<< orphan*/  flag; int /*<<< orphan*/  repeat; int /*<<< orphan*/  max_freq_multiple; } ;
struct TYPE_2__ {int interval; } ;

/* Variables and functions */
 int /*<<< orphan*/  BRCMF_PNO_REPORT_NO_BATCH ; 
 int BRCMF_PNO_SCHED_SCAN_MIN_PERIOD ; 
 scalar_t__ BRCMF_SCAN_ON () ; 
 int ENODATA ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  SCAN ; 
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  brcmf_dbg (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  brcmf_err (char*,int,...) ; 
 int brcmf_pno_get_bucket_channels (struct cfg80211_sched_scan_request*,struct brcmf_pno_config_le*) ; 
 int gcd (int,int) ; 
 struct brcmf_gscan_bucket_config* kcalloc (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct brcmf_gscan_bucket_config*) ; 
 int /*<<< orphan*/  le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct brcmf_pno_config_le*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int brcmf_pno_prep_fwconfig(struct brcmf_pno_info *pi,
				   struct brcmf_pno_config_le *pno_cfg,
				   struct brcmf_gscan_bucket_config **buckets,
				   u32 *scan_freq)
{
	struct cfg80211_sched_scan_request *sr;
	struct brcmf_gscan_bucket_config *fw_buckets;
	int i, err, chidx;

	brcmf_dbg(SCAN, "n_reqs=%d\n", pi->n_reqs);
	if (WARN_ON(!pi->n_reqs))
		return -ENODATA;

	/*
	 * actual scan period is determined using gcd() for each
	 * scheduled scan period.
	 */
	*scan_freq = pi->reqs[0]->scan_plans[0].interval;
	for (i = 1; i < pi->n_reqs; i++) {
		sr = pi->reqs[i];
		*scan_freq = gcd(sr->scan_plans[0].interval, *scan_freq);
	}
	if (*scan_freq < BRCMF_PNO_SCHED_SCAN_MIN_PERIOD) {
		brcmf_dbg(SCAN, "scan period too small, using minimum\n");
		*scan_freq = BRCMF_PNO_SCHED_SCAN_MIN_PERIOD;
	}

	*buckets = NULL;
	fw_buckets = kcalloc(pi->n_reqs, sizeof(*fw_buckets), GFP_KERNEL);
	if (!fw_buckets)
		return -ENOMEM;

	memset(pno_cfg, 0, sizeof(*pno_cfg));
	for (i = 0; i < pi->n_reqs; i++) {
		sr = pi->reqs[i];
		chidx = brcmf_pno_get_bucket_channels(sr, pno_cfg);
		if (chidx < 0) {
			err = chidx;
			goto fail;
		}
		fw_buckets[i].bucket_end_index = chidx - 1;
		fw_buckets[i].bucket_freq_multiple =
			sr->scan_plans[0].interval / *scan_freq;
		/* assure period is non-zero */
		if (!fw_buckets[i].bucket_freq_multiple)
			fw_buckets[i].bucket_freq_multiple = 1;
		fw_buckets[i].flag = BRCMF_PNO_REPORT_NO_BATCH;
	}

	if (BRCMF_SCAN_ON()) {
		brcmf_err("base period=%u\n", *scan_freq);
		for (i = 0; i < pi->n_reqs; i++) {
			brcmf_err("[%d] period %u max %u repeat %u flag %x idx %u\n",
				  i, fw_buckets[i].bucket_freq_multiple,
				  le16_to_cpu(fw_buckets[i].max_freq_multiple),
				  fw_buckets[i].repeat, fw_buckets[i].flag,
				  fw_buckets[i].bucket_end_index);
		}
	}
	*buckets = fw_buckets;
	return pi->n_reqs;

fail:
	kfree(fw_buckets);
	return err;
}