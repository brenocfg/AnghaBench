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
typedef  int /*<<< orphan*/  u32 ;
struct hns_roce_dev {int dummy; } ;
typedef  int /*<<< orphan*/  __le32 ;

/* Variables and functions */
 int ALL_PORT_VAL_OPEN ; 
 int /*<<< orphan*/  ROCEE_GLB_CFG_REG ; 
 int /*<<< orphan*/  ROCEE_GLB_CFG_ROCEE_PORT_ST_M ; 
 int /*<<< orphan*/  ROCEE_GLB_CFG_ROCEE_PORT_ST_S ; 
 int /*<<< orphan*/  cpu_to_le32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  roce_read (struct hns_roce_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  roce_set_field (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  roce_write (struct hns_roce_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void hns_roce_port_enable(struct hns_roce_dev *hr_dev, int enable_flag)
{
	__le32 tmp;
	u32 val;

	if (enable_flag) {
		val = roce_read(hr_dev, ROCEE_GLB_CFG_REG);
		 /* Open all ports */
		tmp = cpu_to_le32(val);
		roce_set_field(tmp, ROCEE_GLB_CFG_ROCEE_PORT_ST_M,
			       ROCEE_GLB_CFG_ROCEE_PORT_ST_S,
			       ALL_PORT_VAL_OPEN);
		val = le32_to_cpu(tmp);
		roce_write(hr_dev, ROCEE_GLB_CFG_REG, val);
	} else {
		val = roce_read(hr_dev, ROCEE_GLB_CFG_REG);
		/* Close all ports */
		tmp = cpu_to_le32(val);
		roce_set_field(tmp, ROCEE_GLB_CFG_ROCEE_PORT_ST_M,
			       ROCEE_GLB_CFG_ROCEE_PORT_ST_S, 0x0);
		val = le32_to_cpu(tmp);
		roce_write(hr_dev, ROCEE_GLB_CFG_REG, val);
	}
}