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
typedef  int u32 ;
struct qlcnic_vf_info {int /*<<< orphan*/  state; } ;

/* Variables and functions */
 int EBUSY ; 
 int /*<<< orphan*/  QLC_BC_VF_CHANNEL ; 
 int /*<<< orphan*/  mdelay (int) ; 
 int /*<<< orphan*/  test_and_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int __qlcnic_sriov_issue_bc_post(struct qlcnic_vf_info *vf)
{
	int ret = -EBUSY;
	u32 timeout = 10000;

	do {
		if (!test_and_set_bit(QLC_BC_VF_CHANNEL, &vf->state)) {
			ret = 0;
			break;
		}
		mdelay(1);
	} while (--timeout);

	return ret;
}