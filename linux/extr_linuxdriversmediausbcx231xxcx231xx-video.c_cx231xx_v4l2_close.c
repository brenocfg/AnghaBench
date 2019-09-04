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
struct file {struct cx231xx_fh* private_data; } ;
struct cx231xx_fh {struct cx231xx* dev; } ;
struct cx231xx {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int cx231xx_close (struct file*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int cx231xx_v4l2_close(struct file *filp)
{
	struct cx231xx_fh *fh = filp->private_data;
	struct cx231xx *dev = fh->dev;
	int rc;

	mutex_lock(&dev->lock);
	rc = cx231xx_close(filp);
	mutex_unlock(&dev->lock);
	return rc;
}