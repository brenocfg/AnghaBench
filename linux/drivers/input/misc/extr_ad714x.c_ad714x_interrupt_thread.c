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
struct ad714x_chip {int /*<<< orphan*/  mutex; TYPE_1__* hw; int /*<<< orphan*/  l_state; int /*<<< orphan*/  (* read ) (struct ad714x_chip*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ;} ;
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_2__ {int button_num; int slider_num; int wheel_num; int touchpad_num; } ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  STG_LOW_INT_STA_REG ; 
 int /*<<< orphan*/  ad714x_button_state_machine (struct ad714x_chip*,int) ; 
 int /*<<< orphan*/  ad714x_slider_state_machine (struct ad714x_chip*,int) ; 
 int /*<<< orphan*/  ad714x_touchpad_state_machine (struct ad714x_chip*,int) ; 
 int /*<<< orphan*/  ad714x_wheel_state_machine (struct ad714x_chip*,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct ad714x_chip*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static irqreturn_t ad714x_interrupt_thread(int irq, void *data)
{
	struct ad714x_chip *ad714x = data;
	int i;

	mutex_lock(&ad714x->mutex);

	ad714x->read(ad714x, STG_LOW_INT_STA_REG, &ad714x->l_state, 3);

	for (i = 0; i < ad714x->hw->button_num; i++)
		ad714x_button_state_machine(ad714x, i);
	for (i = 0; i < ad714x->hw->slider_num; i++)
		ad714x_slider_state_machine(ad714x, i);
	for (i = 0; i < ad714x->hw->wheel_num; i++)
		ad714x_wheel_state_machine(ad714x, i);
	for (i = 0; i < ad714x->hw->touchpad_num; i++)
		ad714x_touchpad_state_machine(ad714x, i);

	mutex_unlock(&ad714x->mutex);

	return IRQ_HANDLED;
}