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
struct aq_nic_s {int /*<<< orphan*/  aq_hw; TYPE_1__* aq_hw_ops; } ;
struct TYPE_2__ {int (* hw_interrupt_moderation_set ) (int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int stub1 (int /*<<< orphan*/ ) ; 

int aq_nic_update_interrupt_moderation_settings(struct aq_nic_s *self)
{
	return self->aq_hw_ops->hw_interrupt_moderation_set(self->aq_hw);
}