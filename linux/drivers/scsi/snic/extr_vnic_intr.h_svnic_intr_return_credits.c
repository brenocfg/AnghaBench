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
typedef  unsigned int u32 ;
struct vnic_intr {TYPE_1__* ctrl; } ;
struct TYPE_2__ {int /*<<< orphan*/  int_credit_return; } ;

/* Variables and functions */
 int VNIC_INTR_RESET_TIMER_SHIFT ; 
 int VNIC_INTR_UNMASK_SHIFT ; 
 int /*<<< orphan*/  iowrite32 (unsigned int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void
svnic_intr_return_credits(struct vnic_intr *intr,
			  unsigned int credits,
			  int unmask,
			  int reset_timer)
{
#define VNIC_INTR_UNMASK_SHIFT		16
#define VNIC_INTR_RESET_TIMER_SHIFT	17

	u32 int_credit_return = (credits & 0xffff) |
		(unmask ? (1 << VNIC_INTR_UNMASK_SHIFT) : 0) |
		(reset_timer ? (1 << VNIC_INTR_RESET_TIMER_SHIFT) : 0);

	iowrite32(int_credit_return, &intr->ctrl->int_credit_return);
}