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
struct beiscsi_hba {int dummy; } ;
struct beiscsi_endpoint {int /*<<< orphan*/  ep_cid; struct beiscsi_hba* phba; } ;

/* Variables and functions */
 int /*<<< orphan*/  BEISCSI_LOG_CONFIG ; 
 int /*<<< orphan*/  KERN_INFO ; 
 int /*<<< orphan*/  beiscsi_flush_cq (struct beiscsi_hba*) ; 
 unsigned int beiscsi_invalidate_cxn (struct beiscsi_hba*,struct beiscsi_endpoint*) ; 
 int /*<<< orphan*/  beiscsi_log (struct beiscsi_hba*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int beiscsi_mccq_compl_wait (struct beiscsi_hba*,unsigned int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 unsigned int beiscsi_upload_cxn (struct beiscsi_hba*,struct beiscsi_endpoint*) ; 
 int /*<<< orphan*/  msleep (int) ; 

__attribute__((used)) static int beiscsi_conn_close(struct beiscsi_endpoint *beiscsi_ep)
{
	struct beiscsi_hba *phba = beiscsi_ep->phba;
	unsigned int tag, attempts;
	int ret;

	/**
	 * Without successfully invalidating and uploading connection
	 * driver can't reuse the CID so attempt more than once.
	 */
	attempts = 0;
	while (attempts++ < 3) {
		tag = beiscsi_invalidate_cxn(phba, beiscsi_ep);
		if (tag) {
			ret = beiscsi_mccq_compl_wait(phba, tag, NULL, NULL);
			if (!ret)
				break;
			beiscsi_log(phba, KERN_INFO, BEISCSI_LOG_CONFIG,
				    "BS_%d : invalidate conn failed cid %d\n",
				    beiscsi_ep->ep_cid);
		}
	}

	/* wait for all completions to arrive, then process them */
	msleep(250);
	/* flush CQ entries */
	beiscsi_flush_cq(phba);

	if (attempts > 3)
		return -1;

	attempts = 0;
	while (attempts++ < 3) {
		tag = beiscsi_upload_cxn(phba, beiscsi_ep);
		if (tag) {
			ret = beiscsi_mccq_compl_wait(phba, tag, NULL, NULL);
			if (!ret)
				break;
			beiscsi_log(phba, KERN_INFO, BEISCSI_LOG_CONFIG,
				    "BS_%d : upload conn failed cid %d\n",
				    beiscsi_ep->ep_cid);
		}
	}
	if (attempts > 3)
		return -1;

	return 0;
}