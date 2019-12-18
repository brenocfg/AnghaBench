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
struct input_dev {int dummy; } ;
struct TYPE_2__ {struct input_dev* input; } ;

/* Variables and functions */
 TYPE_1__ cbas_ec ; 
 int /*<<< orphan*/  cbas_ec_lock ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void cbas_ec_set_input(struct input_dev *input)
{
	/* Take the lock so hammer_event() does not race with us here */
	spin_lock_irq(&cbas_ec_lock);
	cbas_ec.input = input;
	spin_unlock_irq(&cbas_ec_lock);
}