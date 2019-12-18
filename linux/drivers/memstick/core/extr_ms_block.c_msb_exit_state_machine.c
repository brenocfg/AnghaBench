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
struct msb_data {int state; int exit_error; TYPE_1__* card; } ;
struct TYPE_2__ {int /*<<< orphan*/  mrq_complete; int /*<<< orphan*/  next_request; } ;

/* Variables and functions */
 int ENXIO ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  h_msb_default_bad ; 
 int /*<<< orphan*/  msb_invalidate_reg_window (struct msb_data*) ; 

__attribute__((used)) static int msb_exit_state_machine(struct msb_data *msb, int error)
{
	WARN_ON(msb->state == -1);

	msb->state = -1;
	msb->exit_error = error;
	msb->card->next_request = h_msb_default_bad;

	/* Invalidate reg window on errors */
	if (error)
		msb_invalidate_reg_window(msb);

	complete(&msb->card->mrq_complete);
	return -ENXIO;
}