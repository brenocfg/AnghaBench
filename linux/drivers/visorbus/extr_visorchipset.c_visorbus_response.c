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
struct visor_device {int /*<<< orphan*/ * pending_msg_hdr; } ;

/* Variables and functions */
 int /*<<< orphan*/  controlvm_responder (int,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 

void visorbus_response(struct visor_device *bus_info, int response,
		       int controlvm_id)
{
	if (!bus_info->pending_msg_hdr)
		return;

	controlvm_responder(controlvm_id, bus_info->pending_msg_hdr, response);
	kfree(bus_info->pending_msg_hdr);
	bus_info->pending_msg_hdr = NULL;
}