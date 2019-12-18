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
struct qlcnic_adapter {int dummy; } ;

/* Variables and functions */
 int qlcnic_83xx_check_cmd_peg_status (struct qlcnic_adapter*) ; 
 int qlcnic_83xx_check_heartbeat (struct qlcnic_adapter*) ; 

__attribute__((used)) static int qlcnic_83xx_check_hw_status(struct qlcnic_adapter *p_dev)
{
	int err;

	err = qlcnic_83xx_check_cmd_peg_status(p_dev);
	if (err)
		return err;

	err = qlcnic_83xx_check_heartbeat(p_dev);
	if (err)
		return err;

	return err;
}