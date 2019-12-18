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
struct v4l2_fh {int dummy; } ;
struct file {struct v4l2_fh* private_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct v4l2_fh*) ; 
 int /*<<< orphan*/  v4l2_fh_del (struct v4l2_fh*) ; 
 int /*<<< orphan*/  v4l2_fh_exit (struct v4l2_fh*) ; 

int v4l2_fh_release(struct file *filp)
{
	struct v4l2_fh *fh = filp->private_data;

	if (fh) {
		v4l2_fh_del(fh);
		v4l2_fh_exit(fh);
		kfree(fh);
	}
	return 0;
}