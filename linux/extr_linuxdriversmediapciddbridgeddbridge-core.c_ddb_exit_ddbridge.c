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

/* Variables and functions */
 int /*<<< orphan*/  ddb_class_destroy () ; 
 int /*<<< orphan*/  ddb_wq ; 
 int /*<<< orphan*/  destroy_workqueue (int /*<<< orphan*/ ) ; 

int ddb_exit_ddbridge(int stage, int error)
{
	switch (stage) {
	default:
	case 2:
		destroy_workqueue(ddb_wq);
		/* fall-through */
	case 1:
		ddb_class_destroy();
		break;
	}

	return error;
}