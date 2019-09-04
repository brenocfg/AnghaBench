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
struct i40iw_device {int /*<<< orphan*/  close_wq; int /*<<< orphan*/  use_count; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic64_dec_and_test (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

void i40iw_rem_devusecount(struct i40iw_device *iwdev)
{
	if (!atomic64_dec_and_test(&iwdev->use_count))
		return;
	wake_up(&iwdev->close_wq);
}