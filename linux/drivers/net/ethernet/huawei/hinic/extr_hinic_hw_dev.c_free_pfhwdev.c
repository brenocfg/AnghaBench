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
struct hinic_hwdev {int /*<<< orphan*/  hwif; } ;
struct hinic_pfhwdev {int /*<<< orphan*/  pf_to_mgmt; struct hinic_hwdev hwdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  HINIC_MOD_L2NIC ; 
 int /*<<< orphan*/  HINIC_PF_MGMT_INIT ; 
 int /*<<< orphan*/  hinic_pf_to_mgmt_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hinic_set_pf_action (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hinic_unregister_mgmt_msg_cb (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void free_pfhwdev(struct hinic_pfhwdev *pfhwdev)
{
	struct hinic_hwdev *hwdev = &pfhwdev->hwdev;

	hinic_set_pf_action(hwdev->hwif, HINIC_PF_MGMT_INIT);

	hinic_unregister_mgmt_msg_cb(&pfhwdev->pf_to_mgmt, HINIC_MOD_L2NIC);

	hinic_pf_to_mgmt_free(&pfhwdev->pf_to_mgmt);
}