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
typedef  int /*<<< orphan*/  u32 ;
struct hns_roce_dev {int dummy; } ;
typedef  enum ib_mtu { ____Placeholder_ib_mtu } ib_mtu ;
typedef  int /*<<< orphan*/  __le32 ;

/* Variables and functions */
 int PHY_PORT_OFFSET ; 
 scalar_t__ ROCEE_SMAC_H_0_REG ; 
 int /*<<< orphan*/  ROCEE_SMAC_H_ROCEE_PORT_MTU_M ; 
 int /*<<< orphan*/  ROCEE_SMAC_H_ROCEE_PORT_MTU_S ; 
 int /*<<< orphan*/  cpu_to_le32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  roce_read (struct hns_roce_dev*,scalar_t__) ; 
 int /*<<< orphan*/  roce_set_field (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  roce_write (struct hns_roce_dev*,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void hns_roce_v1_set_mtu(struct hns_roce_dev *hr_dev, u8 phy_port,
				enum ib_mtu mtu)
{
	__le32 tmp;
	u32 val;

	val = roce_read(hr_dev,
			ROCEE_SMAC_H_0_REG + phy_port * PHY_PORT_OFFSET);
	tmp = cpu_to_le32(val);
	roce_set_field(tmp, ROCEE_SMAC_H_ROCEE_PORT_MTU_M,
		       ROCEE_SMAC_H_ROCEE_PORT_MTU_S, mtu);
	val = le32_to_cpu(tmp);
	roce_write(hr_dev, ROCEE_SMAC_H_0_REG + phy_port * PHY_PORT_OFFSET,
		   val);
}