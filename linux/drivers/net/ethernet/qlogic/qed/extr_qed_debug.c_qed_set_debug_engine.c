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
struct TYPE_2__ {int engine_for_debug; } ;
struct qed_dev {TYPE_1__ dbg_params; } ;

/* Variables and functions */
 int /*<<< orphan*/  DP_VERBOSE (struct qed_dev*,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  QED_MSG_DEBUG ; 

void qed_set_debug_engine(struct qed_dev *cdev, int engine_number)
{
	DP_VERBOSE(cdev, QED_MSG_DEBUG, "set debug engine to %d\n",
		   engine_number);
	cdev->dbg_params.engine_for_debug = engine_number;
}