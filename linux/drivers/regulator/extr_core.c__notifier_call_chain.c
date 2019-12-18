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
struct regulator_dev {int /*<<< orphan*/  notifier; } ;

/* Variables and functions */
 int blocking_notifier_call_chain (int /*<<< orphan*/ *,unsigned long,void*) ; 

__attribute__((used)) static int _notifier_call_chain(struct regulator_dev *rdev,
				  unsigned long event, void *data)
{
	/* call rdev chain first */
	return blocking_notifier_call_chain(&rdev->notifier, event, data);
}