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
struct st_lsm6dsx_hw {scalar_t__ sip; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_NONE ; 
 int /*<<< orphan*/  IRQ_WAKE_THREAD ; 

__attribute__((used)) static irqreturn_t st_lsm6dsx_handler_irq(int irq, void *private)
{
	struct st_lsm6dsx_hw *hw = private;

	return hw->sip > 0 ? IRQ_WAKE_THREAD : IRQ_NONE;
}