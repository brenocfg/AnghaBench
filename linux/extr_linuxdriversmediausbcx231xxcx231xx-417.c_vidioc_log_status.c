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
struct file {int dummy; } ;
struct cx231xx_fh {struct cx231xx* dev; } ;
struct cx231xx {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  call_all (struct cx231xx*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  core ; 
 int /*<<< orphan*/  log_status ; 
 int v4l2_ctrl_log_status (struct file*,void*) ; 

__attribute__((used)) static int vidioc_log_status(struct file *file, void *priv)
{
	struct cx231xx_fh  *fh  = priv;
	struct cx231xx *dev = fh->dev;

	call_all(dev, core, log_status);
	return v4l2_ctrl_log_status(file, priv);
}