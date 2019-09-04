#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct timer_list {int dummy; } ;
struct TYPE_9__ {int timeout; int /*<<< orphan*/  duration; } ;
struct TYPE_8__ {int /*<<< orphan*/  timeout; } ;
struct TYPE_7__ {TYPE_2__* rcdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEFINE_IR_RAW_EVENT (TYPE_3__) ; 
 TYPE_3__ ev ; 
 int /*<<< orphan*/  ir_raw_event_handle (TYPE_2__*) ; 
 int /*<<< orphan*/  ir_raw_event_store_with_filter (TYPE_2__*,TYPE_3__*) ; 
 TYPE_1__ serial_ir ; 

__attribute__((used)) static void serial_ir_timeout(struct timer_list *unused)
{
	DEFINE_IR_RAW_EVENT(ev);

	ev.timeout = true;
	ev.duration = serial_ir.rcdev->timeout;
	ir_raw_event_store_with_filter(serial_ir.rcdev, &ev);
	ir_raw_event_handle(serial_ir.rcdev);
}