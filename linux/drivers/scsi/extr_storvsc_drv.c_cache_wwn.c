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
struct TYPE_2__ {int /*<<< orphan*/  secondary_port_wwn; int /*<<< orphan*/  secondary_node_wwn; int /*<<< orphan*/  primary_port_wwn; int /*<<< orphan*/  primary_node_wwn; scalar_t__ primary_active; } ;
struct vstor_packet {TYPE_1__ wwn_packet; } ;
struct storvsc_device {void* port_name; void* node_name; } ;

/* Variables and functions */
 void* wwn_to_u64 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void cache_wwn(struct storvsc_device *stor_device,
		      struct vstor_packet *vstor_packet)
{
	/*
	 * Cache the currently active port and node ww names.
	 */
	if (vstor_packet->wwn_packet.primary_active) {
		stor_device->node_name =
			wwn_to_u64(vstor_packet->wwn_packet.primary_node_wwn);
		stor_device->port_name =
			wwn_to_u64(vstor_packet->wwn_packet.primary_port_wwn);
	} else {
		stor_device->node_name =
			wwn_to_u64(vstor_packet->wwn_packet.secondary_node_wwn);
		stor_device->port_name =
			wwn_to_u64(vstor_packet->wwn_packet.secondary_port_wwn);
	}
}