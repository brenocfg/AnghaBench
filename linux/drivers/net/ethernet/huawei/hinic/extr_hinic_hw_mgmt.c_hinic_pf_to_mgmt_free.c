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
struct hinic_hwdev {int /*<<< orphan*/  aeqs; } ;
struct hinic_pfhwdev {struct hinic_hwdev hwdev; } ;
struct hinic_pf_to_mgmt {int /*<<< orphan*/  cmd_chain; } ;

/* Variables and functions */
 int /*<<< orphan*/  HINIC_MSG_FROM_MGMT_CPU ; 
 int /*<<< orphan*/  hinic_aeq_unregister_hw_cb (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hinic_api_cmd_free (int /*<<< orphan*/ ) ; 
 struct hinic_pfhwdev* mgmt_to_pfhwdev (struct hinic_pf_to_mgmt*) ; 

void hinic_pf_to_mgmt_free(struct hinic_pf_to_mgmt *pf_to_mgmt)
{
	struct hinic_pfhwdev *pfhwdev = mgmt_to_pfhwdev(pf_to_mgmt);
	struct hinic_hwdev *hwdev = &pfhwdev->hwdev;

	hinic_aeq_unregister_hw_cb(&hwdev->aeqs, HINIC_MSG_FROM_MGMT_CPU);
	hinic_api_cmd_free(pf_to_mgmt->cmd_chain);
}