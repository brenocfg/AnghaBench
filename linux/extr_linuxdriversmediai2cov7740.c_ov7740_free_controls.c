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
struct TYPE_2__ {int /*<<< orphan*/  ctrl_handler; } ;
struct ov7740 {int /*<<< orphan*/  mutex; TYPE_1__ subdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  mutex_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  v4l2_ctrl_handler_free (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ov7740_free_controls(struct ov7740 *ov7740)
{
	v4l2_ctrl_handler_free(ov7740->subdev.ctrl_handler);
	mutex_destroy(&ov7740->mutex);
}