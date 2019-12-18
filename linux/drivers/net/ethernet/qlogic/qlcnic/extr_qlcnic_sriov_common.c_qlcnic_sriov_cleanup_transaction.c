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
struct qlcnic_bc_trans {struct qlcnic_bc_trans* rsp_hdr; struct qlcnic_bc_trans* req_hdr; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct qlcnic_bc_trans*) ; 

__attribute__((used)) static void qlcnic_sriov_cleanup_transaction(struct qlcnic_bc_trans *trans)
{
	if (!trans)
		return;
	kfree(trans->req_hdr);
	kfree(trans->rsp_hdr);
	kfree(trans);
}