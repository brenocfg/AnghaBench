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
struct hv_per_cpu_context {struct clock_event_device* clk_evt; } ;
struct hv_message {int dummy; } ;
struct clock_event_device {int /*<<< orphan*/  (* event_handler ) (struct clock_event_device*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  HVMSG_TIMER_EXPIRED ; 
 int /*<<< orphan*/  stub1 (struct clock_event_device*) ; 
 int /*<<< orphan*/  vmbus_signal_eom (struct hv_message*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void hv_process_timer_expiration(struct hv_message *msg,
					struct hv_per_cpu_context *hv_cpu)
{
	struct clock_event_device *dev = hv_cpu->clk_evt;

	if (dev->event_handler)
		dev->event_handler(dev);

	vmbus_signal_eom(msg, HVMSG_TIMER_EXPIRED);
}