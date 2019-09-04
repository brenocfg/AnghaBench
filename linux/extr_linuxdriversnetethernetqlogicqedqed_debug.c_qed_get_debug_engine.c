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
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_2__ {int /*<<< orphan*/  engine_for_debug; } ;
struct qed_dev {TYPE_1__ dbg_params; } ;

/* Variables and functions */

u8 qed_get_debug_engine(struct qed_dev *cdev)
{
	return cdev->dbg_params.engine_for_debug;
}