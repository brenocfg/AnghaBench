#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct ethtool_regs {int version; } ;
struct TYPE_4__ {int /*<<< orphan*/  aq_hw_caps; } ;
struct aq_nic_s {TYPE_2__ aq_nic_cfg; int /*<<< orphan*/  aq_hw; TYPE_1__* aq_hw_ops; } ;
struct TYPE_3__ {int (* hw_get_regs ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 int stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int aq_nic_get_regs(struct aq_nic_s *self, struct ethtool_regs *regs, void *p)
{
	u32 *regs_buff = p;
	int err = 0;

	regs->version = 1;

	err = self->aq_hw_ops->hw_get_regs(self->aq_hw,
					   self->aq_nic_cfg.aq_hw_caps,
					   regs_buff);
	if (err < 0)
		goto err_exit;

err_exit:
	return err;
}