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
struct qlcnic_hardware_context {int extend_lb_time; } ;
struct qlcnic_adapter {int /*<<< orphan*/  netdev; struct qlcnic_hardware_context* ahw; } ;

/* Variables and functions */
 int QLC_83XX_LB_MSLEEP_COUNT ; 
 int /*<<< orphan*/  netdev_info (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static void qlcnic_extend_lb_idc_cmpltn_wait(struct qlcnic_adapter *adapter,
					     u32 *max_wait_count)
{
	struct qlcnic_hardware_context *ahw = adapter->ahw;
	int temp;

	netdev_info(adapter->netdev, "Received loopback IDC time extend event for 0x%x seconds\n",
		    ahw->extend_lb_time);
	temp = ahw->extend_lb_time * 1000;
	*max_wait_count += temp / QLC_83XX_LB_MSLEEP_COUNT;
	ahw->extend_lb_time = 0;
}