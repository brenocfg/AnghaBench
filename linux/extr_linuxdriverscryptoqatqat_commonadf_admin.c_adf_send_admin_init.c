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
struct adf_accel_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ICP_QAT_FW_CONSTANTS_CFG ; 
 int /*<<< orphan*/  ICP_QAT_FW_INIT_ME ; 
 int adf_send_admin_cmd (struct adf_accel_dev*,int /*<<< orphan*/ ) ; 

int adf_send_admin_init(struct adf_accel_dev *accel_dev)
{
	int ret = adf_send_admin_cmd(accel_dev, ICP_QAT_FW_INIT_ME);

	if (ret)
		return ret;
	return adf_send_admin_cmd(accel_dev, ICP_QAT_FW_CONSTANTS_CFG);
}