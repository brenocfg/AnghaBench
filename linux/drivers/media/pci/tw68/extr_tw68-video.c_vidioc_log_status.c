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
struct tw68_dev {int dummy; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  tw68_dump_regs (struct tw68_dev*) ; 
 int v4l2_ctrl_log_status (struct file*,void*) ; 
 struct tw68_dev* video_drvdata (struct file*) ; 

__attribute__((used)) static int vidioc_log_status(struct file *file, void *priv)
{
	struct tw68_dev *dev = video_drvdata(file);

	tw68_dump_regs(dev);
	return v4l2_ctrl_log_status(file, priv);
}