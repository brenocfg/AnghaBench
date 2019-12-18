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
struct hfi1_devdata {int /*<<< orphan*/  user_comp; int /*<<< orphan*/  user_refcount; } ;

/* Variables and functions */
 scalar_t__ atomic_dec_and_test (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wait_for_completion (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void wait_for_clients(struct hfi1_devdata *dd)
{
	/*
	 * Remove the device init value and complete the device if there is
	 * no clients or wait for active clients to finish.
	 */
	if (atomic_dec_and_test(&dd->user_refcount))
		complete(&dd->user_comp);

	wait_for_completion(&dd->user_comp);
}