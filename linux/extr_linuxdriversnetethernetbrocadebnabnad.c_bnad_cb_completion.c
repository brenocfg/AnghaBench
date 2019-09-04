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
struct bnad_iocmd_comp {int /*<<< orphan*/  comp; scalar_t__ comp_status; } ;
typedef  enum bfa_status { ____Placeholder_bfa_status } bfa_status ;

/* Variables and functions */
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 

void
bnad_cb_completion(void *arg, enum bfa_status status)
{
	struct bnad_iocmd_comp *iocmd_comp =
			(struct bnad_iocmd_comp *)arg;

	iocmd_comp->comp_status = (u32) status;
	complete(&iocmd_comp->comp);
}