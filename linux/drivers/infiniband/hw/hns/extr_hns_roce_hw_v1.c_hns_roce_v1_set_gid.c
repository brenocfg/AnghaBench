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
union ib_gid {int /*<<< orphan*/ * raw; } ;
typedef  int u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct ib_gid_attr {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  lock; } ;
struct hns_roce_dev {TYPE_1__ iboe; scalar_t__ reg_base; } ;

/* Variables and functions */
 int HNS_ROCE_V1_GID_NUM ; 
 scalar_t__ ROCEE_PORT_GID_H_0_REG ; 
 scalar_t__ ROCEE_PORT_GID_L_0_REG ; 
 scalar_t__ ROCEE_PORT_GID_MH_0_REG ; 
 scalar_t__ ROCEE_PORT_GID_ML_0_REG ; 
 int hns_get_gid_index (struct hns_roce_dev*,int,int) ; 
 int /*<<< orphan*/  roce_raw_write (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int hns_roce_v1_set_gid(struct hns_roce_dev *hr_dev, u8 port,
			       int gid_index, const union ib_gid *gid,
			       const struct ib_gid_attr *attr)
{
	unsigned long flags;
	u32 *p = NULL;
	u8 gid_idx = 0;

	gid_idx = hns_get_gid_index(hr_dev, port, gid_index);

	spin_lock_irqsave(&hr_dev->iboe.lock, flags);

	p = (u32 *)&gid->raw[0];
	roce_raw_write(*p, hr_dev->reg_base + ROCEE_PORT_GID_L_0_REG +
		       (HNS_ROCE_V1_GID_NUM * gid_idx));

	p = (u32 *)&gid->raw[4];
	roce_raw_write(*p, hr_dev->reg_base + ROCEE_PORT_GID_ML_0_REG +
		       (HNS_ROCE_V1_GID_NUM * gid_idx));

	p = (u32 *)&gid->raw[8];
	roce_raw_write(*p, hr_dev->reg_base + ROCEE_PORT_GID_MH_0_REG +
		       (HNS_ROCE_V1_GID_NUM * gid_idx));

	p = (u32 *)&gid->raw[0xc];
	roce_raw_write(*p, hr_dev->reg_base + ROCEE_PORT_GID_H_0_REG +
		       (HNS_ROCE_V1_GID_NUM * gid_idx));

	spin_unlock_irqrestore(&hr_dev->iboe.lock, flags);

	return 0;
}