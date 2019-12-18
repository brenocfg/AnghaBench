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
struct poll_table_struct {int dummy; } ;
struct file {unsigned int f_version; } ;
typedef  int __poll_t ;
struct TYPE_2__ {int /*<<< orphan*/  count; int /*<<< orphan*/  wait; } ;

/* Variables and functions */
 int EPOLLIN ; 
 int EPOLLRDNORM ; 
 unsigned int atomic_read (int /*<<< orphan*/ *) ; 
 TYPE_1__ device_event ; 
 int /*<<< orphan*/  poll_wait (struct file*,int /*<<< orphan*/ *,struct poll_table_struct*) ; 

__attribute__((used)) static __poll_t usb_device_poll(struct file *file,
				    struct poll_table_struct *wait)
{
	unsigned int event_count;

	poll_wait(file, &device_event.wait, wait);

	event_count = atomic_read(&device_event.count);
	if (file->f_version != event_count) {
		file->f_version = event_count;
		return EPOLLIN | EPOLLRDNORM;
	}

	return 0;
}