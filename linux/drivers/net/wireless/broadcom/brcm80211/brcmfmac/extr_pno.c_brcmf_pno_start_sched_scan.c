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
struct cfg80211_sched_scan_request {int /*<<< orphan*/  reqid; } ;
struct brcmf_pno_info {scalar_t__ n_reqs; } ;
struct brcmf_if {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  TRACE ; 
 int /*<<< orphan*/  brcmf_dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int brcmf_pno_config_sched_scans (struct brcmf_if*) ; 
 int /*<<< orphan*/  brcmf_pno_remove_request (struct brcmf_pno_info*,int /*<<< orphan*/ ) ; 
 int brcmf_pno_store_request (struct brcmf_pno_info*,struct cfg80211_sched_scan_request*) ; 
 struct brcmf_pno_info* ifp_to_pno (struct brcmf_if*) ; 

int brcmf_pno_start_sched_scan(struct brcmf_if *ifp,
			       struct cfg80211_sched_scan_request *req)
{
	struct brcmf_pno_info *pi;
	int ret;

	brcmf_dbg(TRACE, "reqid=%llu\n", req->reqid);

	pi = ifp_to_pno(ifp);
	ret = brcmf_pno_store_request(pi, req);
	if (ret < 0)
		return ret;

	ret = brcmf_pno_config_sched_scans(ifp);
	if (ret < 0) {
		brcmf_pno_remove_request(pi, req->reqid);
		if (pi->n_reqs)
			(void)brcmf_pno_config_sched_scans(ifp);
		return ret;
	}
	return 0;
}