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
struct skcipher_request {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  orh; int /*<<< orphan*/  completion; } ;
struct nitrox_softreq {TYPE_1__ resp; struct skcipher_request* skreq; int /*<<< orphan*/  (* callback ) (struct skcipher_request*,int) ;int /*<<< orphan*/  tstamp; int /*<<< orphan*/  status; } ;
struct nitrox_device {int /*<<< orphan*/  timeout; } ;
struct nitrox_cmdq {int /*<<< orphan*/  pending_count; struct nitrox_device* ndev; } ;
typedef  int /*<<< orphan*/  (* completion_t ) (struct skcipher_request*,int) ;

/* Variables and functions */
 int /*<<< orphan*/  DEV (struct nitrox_device*) ; 
 int READ_ONCE (int /*<<< orphan*/ ) ; 
 scalar_t__ REQ_POSTED ; 
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cmd_timeout (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err_ratelimited (int /*<<< orphan*/ ,char*,int) ; 
 struct nitrox_softreq* get_first_response_entry (struct nitrox_cmdq*) ; 
 int /*<<< orphan*/  response_list_del (struct nitrox_softreq*,struct nitrox_cmdq*) ; 
 int /*<<< orphan*/  smp_mb__after_atomic () ; 
 int /*<<< orphan*/  softreq_destroy (struct nitrox_softreq*) ; 

__attribute__((used)) static void process_response_list(struct nitrox_cmdq *cmdq)
{
	struct nitrox_device *ndev = cmdq->ndev;
	struct nitrox_softreq *sr;
	struct skcipher_request *skreq;
	completion_t callback;
	int req_completed = 0, err = 0, budget;

	/* check all pending requests */
	budget = atomic_read(&cmdq->pending_count);

	while (req_completed < budget) {
		sr = get_first_response_entry(cmdq);
		if (!sr)
			break;

		if (atomic_read(&sr->status) != REQ_POSTED)
			break;

		/* check orh and completion bytes updates */
		if (READ_ONCE(sr->resp.orh) == READ_ONCE(sr->resp.completion)) {
			/* request not completed, check for timeout */
			if (!cmd_timeout(sr->tstamp, ndev->timeout))
				break;
			dev_err_ratelimited(DEV(ndev),
					    "Request timeout, orh 0x%016llx\n",
					    READ_ONCE(sr->resp.orh));
		}
		atomic_dec(&cmdq->pending_count);
		/* sync with other cpus */
		smp_mb__after_atomic();
		/* remove from response list */
		response_list_del(sr, cmdq);

		callback = sr->callback;
		skreq = sr->skreq;

		/* ORH error code */
		err = READ_ONCE(sr->resp.orh) & 0xff;
		softreq_destroy(sr);

		if (callback)
			callback(skreq, err);

		req_completed++;
	}
}