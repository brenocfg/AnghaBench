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
struct wl1273_device {scalar_t__ rd_index; scalar_t__ wr_index; int /*<<< orphan*/  read_queue; struct file* owner; struct wl1273_core* core; } ;
struct wl1273_core {scalar_t__ mode; } ;
struct poll_table_struct {int dummy; } ;
struct file {int dummy; } ;
typedef  int __poll_t ;

/* Variables and functions */
 int EPOLLERR ; 
 int EPOLLIN ; 
 int EPOLLOUT ; 
 int EPOLLRDNORM ; 
 int EPOLLWRNORM ; 
 scalar_t__ WL1273_MODE_RX ; 
 scalar_t__ WL1273_MODE_TX ; 
 int /*<<< orphan*/  poll_wait (struct file*,int /*<<< orphan*/ *,struct poll_table_struct*) ; 
 int /*<<< orphan*/  video_devdata (struct file*) ; 
 struct wl1273_device* video_get_drvdata (int /*<<< orphan*/ ) ; 

__attribute__((used)) static __poll_t wl1273_fm_fops_poll(struct file *file,
					struct poll_table_struct *pts)
{
	struct wl1273_device *radio = video_get_drvdata(video_devdata(file));
	struct wl1273_core *core = radio->core;

	if (radio->owner && radio->owner != file)
		return EPOLLERR;

	radio->owner = file;

	if (core->mode == WL1273_MODE_RX) {
		poll_wait(file, &radio->read_queue, pts);

		if (radio->rd_index != radio->wr_index)
			return EPOLLIN | EPOLLRDNORM;

	} else if (core->mode == WL1273_MODE_TX) {
		return EPOLLOUT | EPOLLWRNORM;
	}

	return 0;
}