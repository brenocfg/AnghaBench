#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct rc_dev {int dummy; } ;
struct TYPE_4__ {int timeout; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEFINE_IR_RAW_EVENT (TYPE_1__) ; 
 TYPE_1__ ev ; 
 int /*<<< orphan*/  ir_raw_event_store (struct rc_dev*,TYPE_1__*) ; 

__attribute__((used)) static void st_rc_send_lirc_timeout(struct rc_dev *rdev)
{
	DEFINE_IR_RAW_EVENT(ev);
	ev.timeout = true;
	ir_raw_event_store(rdev, &ev);
}