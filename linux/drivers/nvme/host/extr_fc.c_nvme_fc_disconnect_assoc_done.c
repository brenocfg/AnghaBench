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
struct nvmefc_ls_req_op {int dummy; } ;
struct nvmefc_ls_req {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  __nvme_fc_finish_ls_req (struct nvmefc_ls_req_op*) ; 
 int /*<<< orphan*/  kfree (struct nvmefc_ls_req_op*) ; 
 struct nvmefc_ls_req_op* ls_req_to_lsop (struct nvmefc_ls_req*) ; 

__attribute__((used)) static void
nvme_fc_disconnect_assoc_done(struct nvmefc_ls_req *lsreq, int status)
{
	struct nvmefc_ls_req_op *lsop = ls_req_to_lsop(lsreq);

	__nvme_fc_finish_ls_req(lsop);

	/* fc-nvme initiator doesn't care about success or failure of cmd */

	kfree(lsop);
}