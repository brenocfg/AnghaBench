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
struct brcmf_pno_info {scalar_t__ n_reqs; int /*<<< orphan*/  req_lock; struct cfg80211_sched_scan_request** reqs; } ;

/* Variables and functions */
 scalar_t__ BRCMF_PNO_MAX_BUCKETS ; 
 int ENOSPC ; 
 int /*<<< orphan*/  SCAN ; 
 scalar_t__ WARN (int,char*) ; 
 int /*<<< orphan*/  brcmf_dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int brcmf_pno_store_request(struct brcmf_pno_info *pi,
				   struct cfg80211_sched_scan_request *req)
{
	if (WARN(pi->n_reqs == BRCMF_PNO_MAX_BUCKETS,
		 "pno request storage full\n"))
		return -ENOSPC;

	brcmf_dbg(SCAN, "reqid=%llu\n", req->reqid);
	mutex_lock(&pi->req_lock);
	pi->reqs[pi->n_reqs++] = req;
	mutex_unlock(&pi->req_lock);
	return 0;
}