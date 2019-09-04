#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct video_device {int /*<<< orphan*/  ctrl_handler; } ;
struct file {int dummy; } ;
struct bttv_fh {struct bttv* btv; } ;
struct TYPE_3__ {int /*<<< orphan*/  name; } ;
struct TYPE_4__ {TYPE_1__ v4l2_dev; } ;
struct bttv {TYPE_2__ c; } ;

/* Variables and functions */
 int /*<<< orphan*/  bttv_call_all (struct bttv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  core ; 
 int /*<<< orphan*/  log_status ; 
 int /*<<< orphan*/  v4l2_ctrl_handler_log_status (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct video_device* video_devdata (struct file*) ; 

__attribute__((used)) static int bttv_log_status(struct file *file, void *f)
{
	struct video_device *vdev = video_devdata(file);
	struct bttv_fh *fh  = f;
	struct bttv *btv = fh->btv;

	v4l2_ctrl_handler_log_status(vdev->ctrl_handler, btv->c.v4l2_dev.name);
	bttv_call_all(btv, core, log_status);
	return 0;
}