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
typedef  int /*<<< orphan*/  u64 ;
struct iio_event_interface {int /*<<< orphan*/  wait; int /*<<< orphan*/  det_events; } ;
struct iio_event_data {int /*<<< orphan*/  timestamp; int /*<<< orphan*/  id; } ;
struct iio_dev {struct iio_event_interface* event_interface; } ;
typedef  int /*<<< orphan*/  s64 ;

/* Variables and functions */
 int /*<<< orphan*/  EPOLLIN ; 
 scalar_t__ iio_event_enabled (struct iio_event_interface*) ; 
 int kfifo_put (int /*<<< orphan*/ *,struct iio_event_data) ; 
 int /*<<< orphan*/  wake_up_poll (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int iio_push_event(struct iio_dev *indio_dev, u64 ev_code, s64 timestamp)
{
	struct iio_event_interface *ev_int = indio_dev->event_interface;
	struct iio_event_data ev;
	int copied;

	if (!ev_int)
		return 0;

	/* Does anyone care? */
	if (iio_event_enabled(ev_int)) {

		ev.id = ev_code;
		ev.timestamp = timestamp;

		copied = kfifo_put(&ev_int->det_events, ev);
		if (copied != 0)
			wake_up_poll(&ev_int->wait, EPOLLIN);
	}

	return 0;
}