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
struct poll_table_struct {int dummy; } ;
struct iio_event_interface {int /*<<< orphan*/  det_events; int /*<<< orphan*/  wait; } ;
struct iio_dev {int /*<<< orphan*/  info; struct iio_event_interface* event_interface; } ;
struct file {struct iio_dev* private_data; } ;
typedef  int __poll_t ;

/* Variables and functions */
 int EPOLLIN ; 
 int EPOLLRDNORM ; 
 int /*<<< orphan*/  kfifo_is_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  poll_wait (struct file*,int /*<<< orphan*/ *,struct poll_table_struct*) ; 

__attribute__((used)) static __poll_t iio_event_poll(struct file *filep,
			     struct poll_table_struct *wait)
{
	struct iio_dev *indio_dev = filep->private_data;
	struct iio_event_interface *ev_int = indio_dev->event_interface;
	__poll_t events = 0;

	if (!indio_dev->info)
		return events;

	poll_wait(filep, &ev_int->wait, wait);

	if (!kfifo_is_empty(&ev_int->det_events))
		events = EPOLLIN | EPOLLRDNORM;

	return events;
}