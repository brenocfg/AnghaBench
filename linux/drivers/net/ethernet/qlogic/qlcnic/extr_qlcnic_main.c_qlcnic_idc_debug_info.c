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
typedef  int u8 ;
typedef  int u32 ;
struct qlcnic_adapter {int portnum; int dev_rst_time; } ;

/* Variables and functions */
 int /*<<< orphan*/  QLCNIC_CRB_DRV_SCRATCH ; 
 int /*<<< orphan*/  QLC_SHARED_REG_WR32 (struct qlcnic_adapter*,int /*<<< orphan*/ ,int) ; 
 int jiffies ; 

__attribute__((used)) static void
qlcnic_idc_debug_info(struct qlcnic_adapter *adapter, u8 encoding)
{
	u32 val;

	val = adapter->portnum & 0xf;
	val |= encoding << 7;
	val |= (jiffies - adapter->dev_rst_time) << 8;

	QLC_SHARED_REG_WR32(adapter, QLCNIC_CRB_DRV_SCRATCH, val);
	adapter->dev_rst_time = jiffies;
}