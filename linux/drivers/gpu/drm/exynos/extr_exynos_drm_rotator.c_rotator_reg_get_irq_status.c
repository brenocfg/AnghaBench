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
typedef  scalar_t__ u32 ;
struct rot_context {int dummy; } ;
typedef  enum rot_irq_status { ____Placeholder_rot_irq_status } rot_irq_status ;

/* Variables and functions */
 int ROT_IRQ_STATUS_COMPLETE ; 
 int ROT_IRQ_STATUS_ILLEGAL ; 
 int /*<<< orphan*/  ROT_STATUS ; 
 scalar_t__ ROT_STATUS_IRQ (scalar_t__) ; 
 scalar_t__ ROT_STATUS_IRQ_VAL_COMPLETE ; 
 scalar_t__ rot_read (int /*<<< orphan*/ ) ; 

__attribute__((used)) static enum rot_irq_status rotator_reg_get_irq_status(struct rot_context *rot)
{
	u32 val = rot_read(ROT_STATUS);

	val = ROT_STATUS_IRQ(val);

	if (val == ROT_STATUS_IRQ_VAL_COMPLETE)
		return ROT_IRQ_STATUS_COMPLETE;

	return ROT_IRQ_STATUS_ILLEGAL;
}