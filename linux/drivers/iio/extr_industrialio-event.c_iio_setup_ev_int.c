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
struct iio_event_interface {int /*<<< orphan*/  read_lock; int /*<<< orphan*/  wait; int /*<<< orphan*/  det_events; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_KFIFO (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void iio_setup_ev_int(struct iio_event_interface *ev_int)
{
	INIT_KFIFO(ev_int->det_events);
	init_waitqueue_head(&ev_int->wait);
	mutex_init(&ev_int->read_lock);
}