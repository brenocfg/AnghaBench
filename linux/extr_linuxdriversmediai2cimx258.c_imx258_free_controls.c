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
struct imx258 {int /*<<< orphan*/  mutex; TYPE_1__ sd; } ;

/* Variables and functions */
 int /*<<< orphan*/  mutex_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  v4l2_ctrl_handler_free (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void imx258_free_controls(struct imx258 *imx258)
{
	v4l2_ctrl_handler_free(imx258->sd.ctrl_handler);
	mutex_destroy(&imx258->mutex);
}