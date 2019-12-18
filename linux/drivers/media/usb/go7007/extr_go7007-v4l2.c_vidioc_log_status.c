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
struct go7007 {int /*<<< orphan*/  v4l2_dev; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int call_all (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  core ; 
 int /*<<< orphan*/  log_status ; 
 int /*<<< orphan*/  v4l2_ctrl_log_status (struct file*,void*) ; 
 struct go7007* video_drvdata (struct file*) ; 

__attribute__((used)) static int vidioc_log_status(struct file *file, void *priv)
{
	struct go7007 *go = video_drvdata(file);

	v4l2_ctrl_log_status(file, priv);
	return call_all(&go->v4l2_dev, core, log_status);
}