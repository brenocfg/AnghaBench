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
struct kfd_dbgdev {int /*<<< orphan*/ * kq; } ;

/* Variables and functions */

__attribute__((used)) static int dbgdev_register_nodiq(struct kfd_dbgdev *dbgdev)
{
	/*
	 * no action is needed in this case,
	 * just make sure diq will not be used
	 */

	dbgdev->kq = NULL;

	return 0;
}