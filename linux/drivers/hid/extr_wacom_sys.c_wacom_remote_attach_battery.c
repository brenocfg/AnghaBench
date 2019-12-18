#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct wacom_remote {TYPE_3__* remotes; } ;
struct TYPE_6__ {TYPE_1__* groups; } ;
struct wacom {struct wacom_remote* remote; TYPE_2__ led; } ;
struct TYPE_8__ {scalar_t__ battery; } ;
struct TYPE_7__ {TYPE_4__ battery; int /*<<< orphan*/  registered; } ;
struct TYPE_5__ {scalar_t__ select; } ;

/* Variables and functions */
 scalar_t__ WACOM_STATUS_UNKNOWN ; 
 int __wacom_initialize_battery (struct wacom*,TYPE_4__*) ; 

__attribute__((used)) static int wacom_remote_attach_battery(struct wacom *wacom, int index)
{
	struct wacom_remote *remote = wacom->remote;
	int error;

	if (!remote->remotes[index].registered)
		return 0;

	if (remote->remotes[index].battery.battery)
		return 0;

	if (wacom->led.groups[index].select == WACOM_STATUS_UNKNOWN)
		return 0;

	error = __wacom_initialize_battery(wacom,
					&wacom->remote->remotes[index].battery);
	if (error)
		return error;

	return 0;
}