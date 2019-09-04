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
struct radio_tea5777 {TYPE_1__ vd; } ;

/* Variables and functions */
 int /*<<< orphan*/  v4l2_ctrl_handler_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  video_unregister_device (TYPE_1__*) ; 

void radio_tea5777_exit(struct radio_tea5777 *tea)
{
	video_unregister_device(&tea->vd);
	v4l2_ctrl_handler_free(tea->vd.ctrl_handler);
}