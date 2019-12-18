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
struct mxt_data {int /*<<< orphan*/  irq; } ;

/* Variables and functions */
 int /*<<< orphan*/  enable_irq (int /*<<< orphan*/ ) ; 
 int mxt_process_messages_until_invalid (struct mxt_data*) ; 

__attribute__((used)) static int mxt_acquire_irq(struct mxt_data *data)
{
	int error;

	enable_irq(data->irq);

	error = mxt_process_messages_until_invalid(data);
	if (error)
		return error;

	return 0;
}