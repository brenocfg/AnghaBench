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
struct file {struct fb_open_file* private_data; } ;
struct fieldbus_dev {scalar_t__ dc_event; int /*<<< orphan*/  dc_wq; } ;
struct fb_open_file {scalar_t__ dc_event; struct fieldbus_dev* fbdev; } ;
typedef  int /*<<< orphan*/  poll_table ;
typedef  int __poll_t ;

/* Variables and functions */
 int EPOLLERR ; 
 int EPOLLIN ; 
 int EPOLLOUT ; 
 int EPOLLPRI ; 
 int EPOLLRDNORM ; 
 int EPOLLWRNORM ; 
 int /*<<< orphan*/  poll_wait (struct file*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static __poll_t fieldbus_poll(struct file *filp, poll_table *wait)
{
	struct fb_open_file *of = filp->private_data;
	struct fieldbus_dev *fbdev = of->fbdev;
	__poll_t mask = EPOLLIN | EPOLLRDNORM | EPOLLOUT | EPOLLWRNORM;

	poll_wait(filp, &fbdev->dc_wq, wait);
	/* data changed ? */
	if (fbdev->dc_event != of->dc_event)
		mask |= EPOLLPRI | EPOLLERR;
	return mask;
}