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
struct aq_nic_s {unsigned int packet_filter; int /*<<< orphan*/  aq_hw; TYPE_1__* aq_hw_ops; } ;
struct TYPE_2__ {int (* hw_packet_filter_set ) (int /*<<< orphan*/ ,unsigned int) ;} ;

/* Variables and functions */
 int stub1 (int /*<<< orphan*/ ,unsigned int) ; 

int aq_nic_set_packet_filter(struct aq_nic_s *self, unsigned int flags)
{
	int err = 0;

	err = self->aq_hw_ops->hw_packet_filter_set(self->aq_hw, flags);
	if (err < 0)
		goto err_exit;

	self->packet_filter = flags;

err_exit:
	return err;
}