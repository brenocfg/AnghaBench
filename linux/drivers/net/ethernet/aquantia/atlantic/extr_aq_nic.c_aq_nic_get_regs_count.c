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
struct TYPE_4__ {TYPE_1__* aq_hw_caps; } ;
struct aq_nic_s {TYPE_2__ aq_nic_cfg; } ;
struct TYPE_3__ {int mac_regs_count; } ;

/* Variables and functions */

int aq_nic_get_regs_count(struct aq_nic_s *self)
{
	return self->aq_nic_cfg.aq_hw_caps->mac_regs_count;
}