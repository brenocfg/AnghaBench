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
struct TYPE_7__ {scalar_t__ response_expected; } ;
struct controlvm_message_header {TYPE_3__ flags; } ;
struct TYPE_8__ {TYPE_2__* acpi_device; } ;
struct TYPE_5__ {int /*<<< orphan*/  kobj; } ;
struct TYPE_6__ {TYPE_1__ dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  KOBJ_ONLINE ; 
 TYPE_4__* chipset_dev ; 
 int /*<<< orphan*/  controlvm_respond (struct controlvm_message_header*,int,int /*<<< orphan*/ *) ; 
 int kobject_uevent (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int chipset_ready_uevent(struct controlvm_message_header *msg_hdr)
{
	int res;

	res = kobject_uevent(&chipset_dev->acpi_device->dev.kobj, KOBJ_ONLINE);
	if (msg_hdr->flags.response_expected)
		controlvm_respond(msg_hdr, res, NULL);
	return res;
}