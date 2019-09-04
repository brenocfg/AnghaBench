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
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_2__ {int /*<<< orphan*/  port_num; } ;
struct ib_event {int /*<<< orphan*/  event; TYPE_1__ element; struct ib_device* device; } ;
struct ib_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  IB_EVENT_GID_CHANGE ; 
 int /*<<< orphan*/  ib_dispatch_event (struct ib_event*) ; 

__attribute__((used)) static void dispatch_gid_change_event(struct ib_device *ib_dev, u8 port)
{
	struct ib_event event;

	event.device		= ib_dev;
	event.element.port_num	= port;
	event.event		= IB_EVENT_GID_CHANGE;

	ib_dispatch_event(&event);
}