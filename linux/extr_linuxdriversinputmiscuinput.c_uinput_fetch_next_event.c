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
struct uinput_device {size_t head; size_t tail; TYPE_1__* dev; struct input_event* buff; } ;
struct input_event {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  event_lock; } ;

/* Variables and functions */
 int UINPUT_BUFFER_SIZE ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool uinput_fetch_next_event(struct uinput_device *udev,
				    struct input_event *event)
{
	bool have_event;

	spin_lock_irq(&udev->dev->event_lock);

	have_event = udev->head != udev->tail;
	if (have_event) {
		*event = udev->buff[udev->tail];
		udev->tail = (udev->tail + 1) % UINPUT_BUFFER_SIZE;
	}

	spin_unlock_irq(&udev->dev->event_lock);

	return have_event;
}