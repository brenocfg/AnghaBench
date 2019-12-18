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
struct gb_svc {int /*<<< orphan*/  device_id_map; int /*<<< orphan*/  ap_intf_id; } ;
struct gb_interface {int /*<<< orphan*/  device_id; int /*<<< orphan*/  interface_id; TYPE_1__* hd; } ;
struct TYPE_2__ {struct gb_svc* svc; } ;

/* Variables and functions */
 int /*<<< orphan*/  GB_INTERFACE_DEVICE_ID_BAD ; 
 int /*<<< orphan*/  gb_svc_route_destroy (struct gb_svc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ida_simple_remove (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void gb_interface_route_destroy(struct gb_interface *intf)
{
	struct gb_svc *svc = intf->hd->svc;

	if (intf->device_id == GB_INTERFACE_DEVICE_ID_BAD)
		return;

	gb_svc_route_destroy(svc, svc->ap_intf_id, intf->interface_id);
	ida_simple_remove(&svc->device_id_map, intf->device_id);
	intf->device_id = GB_INTERFACE_DEVICE_ID_BAD;
}