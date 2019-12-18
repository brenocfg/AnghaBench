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
typedef  int /*<<< orphan*/  u64 ;
struct brcmf_pno_info {scalar_t__ n_reqs; } ;
struct brcmf_if {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  TRACE ; 
 int /*<<< orphan*/  brcmf_dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  brcmf_pno_clean (struct brcmf_if*) ; 
 int /*<<< orphan*/  brcmf_pno_config_sched_scans (struct brcmf_if*) ; 
 int brcmf_pno_remove_request (struct brcmf_pno_info*,int /*<<< orphan*/ ) ; 
 struct brcmf_pno_info* ifp_to_pno (struct brcmf_if*) ; 

int brcmf_pno_stop_sched_scan(struct brcmf_if *ifp, u64 reqid)
{
	struct brcmf_pno_info *pi;
	int err;

	brcmf_dbg(TRACE, "reqid=%llu\n", reqid);

	pi = ifp_to_pno(ifp);

	/* No PNO request */
	if (!pi->n_reqs)
		return 0;

	err = brcmf_pno_remove_request(pi, reqid);
	if (err)
		return err;

	brcmf_pno_clean(ifp);

	if (pi->n_reqs)
		(void)brcmf_pno_config_sched_scans(ifp);

	return 0;
}