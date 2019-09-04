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
struct TYPE_2__ {int* arg; } ;
struct qlcnic_cmd_args {TYPE_1__ req; } ;

/* Variables and functions */
 int EINVAL ; 

__attribute__((used)) static int qlcnic_sriov_validate_create_rx_ctx(struct qlcnic_cmd_args *cmd)
{
	if ((cmd->req.arg[0] >> 29) != 0x3)
		return -EINVAL;

	return 0;
}