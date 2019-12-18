#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ expires; } ;
struct dmx_sct_filter_params {int timeout; } ;
struct TYPE_4__ {struct dmx_sct_filter_params sec; } ;
struct dmxdev_filter {TYPE_2__ timer; TYPE_1__ params; } ;

/* Variables and functions */
 int HZ ; 
 int /*<<< orphan*/  add_timer (TYPE_2__*) ; 
 int /*<<< orphan*/  del_timer (TYPE_2__*) ; 
 scalar_t__ jiffies ; 

__attribute__((used)) static void dvb_dmxdev_filter_timer(struct dmxdev_filter *dmxdevfilter)
{
	struct dmx_sct_filter_params *para = &dmxdevfilter->params.sec;

	del_timer(&dmxdevfilter->timer);
	if (para->timeout) {
		dmxdevfilter->timer.expires =
		    jiffies + 1 + (HZ / 2 + HZ * para->timeout) / 1000;
		add_timer(&dmxdevfilter->timer);
	}
}