#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  function; } ;
struct TYPE_4__ {int /*<<< orphan*/  release; int /*<<< orphan*/  groups; int /*<<< orphan*/  class; } ;
struct rtc_device {int set_offset_nsec; int irq_freq; int max_user_freq; scalar_t__ pie_enabled; TYPE_1__ pie_timer; int /*<<< orphan*/  uie_rtctimer; int /*<<< orphan*/  aie_timer; int /*<<< orphan*/  irqwork; int /*<<< orphan*/  timerqueue; int /*<<< orphan*/  irq_queue; int /*<<< orphan*/  irq_lock; int /*<<< orphan*/  ops_lock; TYPE_2__ dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  CLOCK_MONOTONIC ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  HRTIMER_MODE_REL ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int NSEC_PER_SEC ; 
 int /*<<< orphan*/  device_initialize (TYPE_2__*) ; 
 int /*<<< orphan*/  hrtimer_init (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 struct rtc_device* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rtc_aie_update_irq ; 
 int /*<<< orphan*/  rtc_class ; 
 int /*<<< orphan*/  rtc_device_release ; 
 int /*<<< orphan*/  rtc_get_dev_attribute_groups () ; 
 int /*<<< orphan*/  rtc_pie_update_irq ; 
 int /*<<< orphan*/  rtc_timer_do_work ; 
 int /*<<< orphan*/  rtc_timer_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct rtc_device*) ; 
 int /*<<< orphan*/  rtc_uie_update_irq ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  timerqueue_init_head (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct rtc_device *rtc_allocate_device(void)
{
	struct rtc_device *rtc;

	rtc = kzalloc(sizeof(*rtc), GFP_KERNEL);
	if (!rtc)
		return NULL;

	device_initialize(&rtc->dev);

	/* Drivers can revise this default after allocating the device. */
	rtc->set_offset_nsec =  NSEC_PER_SEC / 2;

	rtc->irq_freq = 1;
	rtc->max_user_freq = 64;
	rtc->dev.class = rtc_class;
	rtc->dev.groups = rtc_get_dev_attribute_groups();
	rtc->dev.release = rtc_device_release;

	mutex_init(&rtc->ops_lock);
	spin_lock_init(&rtc->irq_lock);
	init_waitqueue_head(&rtc->irq_queue);

	/* Init timerqueue */
	timerqueue_init_head(&rtc->timerqueue);
	INIT_WORK(&rtc->irqwork, rtc_timer_do_work);
	/* Init aie timer */
	rtc_timer_init(&rtc->aie_timer, rtc_aie_update_irq, rtc);
	/* Init uie timer */
	rtc_timer_init(&rtc->uie_rtctimer, rtc_uie_update_irq, rtc);
	/* Init pie timer */
	hrtimer_init(&rtc->pie_timer, CLOCK_MONOTONIC, HRTIMER_MODE_REL);
	rtc->pie_timer.function = rtc_pie_update_irq;
	rtc->pie_enabled = 0;

	return rtc;
}