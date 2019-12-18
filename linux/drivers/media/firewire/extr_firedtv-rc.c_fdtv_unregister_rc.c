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
struct firedtv {TYPE_1__* remote_ctrl_dev; int /*<<< orphan*/  remote_ctrl_work; } ;
struct TYPE_2__ {int /*<<< orphan*/  keycode; } ;

/* Variables and functions */
 int /*<<< orphan*/  cancel_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  input_unregister_device (TYPE_1__*) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 

void fdtv_unregister_rc(struct firedtv *fdtv)
{
	cancel_work_sync(&fdtv->remote_ctrl_work);
	kfree(fdtv->remote_ctrl_dev->keycode);
	input_unregister_device(fdtv->remote_ctrl_dev);
}