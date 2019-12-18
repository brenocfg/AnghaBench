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
struct aq_vec_s {int /*<<< orphan*/  napi; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 int /*<<< orphan*/  napi_schedule (int /*<<< orphan*/ *) ; 

irqreturn_t aq_vec_isr(int irq, void *private)
{
	struct aq_vec_s *self = private;
	int err = 0;

	if (!self) {
		err = -EINVAL;
		goto err_exit;
	}
	napi_schedule(&self->napi);

err_exit:
	return err >= 0 ? IRQ_HANDLED : IRQ_NONE;
}