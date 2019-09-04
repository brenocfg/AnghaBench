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
typedef  scalar_t__ u8 ;
struct hwrm_selftest_exec_output {scalar_t__ test_success; } ;
struct hwrm_selftest_exec_input {scalar_t__ flags; int /*<<< orphan*/  member_0; } ;
struct bnxt {int /*<<< orphan*/  hwrm_cmd_lock; TYPE_1__* test_info; struct hwrm_selftest_exec_output* hwrm_cmd_resp_addr; } ;
typedef  int /*<<< orphan*/  req ;
struct TYPE_2__ {int /*<<< orphan*/  timeout; } ;

/* Variables and functions */
 int /*<<< orphan*/  HWRM_SELFTEST_EXEC ; 
 int _hwrm_send_message (struct bnxt*,struct hwrm_selftest_exec_input*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bnxt_hwrm_cmd_hdr_init (struct bnxt*,struct hwrm_selftest_exec_input*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int bnxt_run_fw_tests(struct bnxt *bp, u8 test_mask, u8 *test_results)
{
	struct hwrm_selftest_exec_output *resp = bp->hwrm_cmd_resp_addr;
	struct hwrm_selftest_exec_input req = {0};
	int rc;

	bnxt_hwrm_cmd_hdr_init(bp, &req, HWRM_SELFTEST_EXEC, -1, -1);
	mutex_lock(&bp->hwrm_cmd_lock);
	resp->test_success = 0;
	req.flags = test_mask;
	rc = _hwrm_send_message(bp, &req, sizeof(req), bp->test_info->timeout);
	*test_results = resp->test_success;
	mutex_unlock(&bp->hwrm_cmd_lock);
	return rc;
}