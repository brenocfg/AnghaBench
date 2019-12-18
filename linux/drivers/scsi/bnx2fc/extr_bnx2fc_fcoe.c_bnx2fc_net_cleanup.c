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
struct bnx2fc_interface {int /*<<< orphan*/  fip_packet_type; int /*<<< orphan*/  fcoe_packet_type; } ;

/* Variables and functions */
 int /*<<< orphan*/  __dev_remove_pack (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  synchronize_net () ; 

__attribute__((used)) static void bnx2fc_net_cleanup(struct bnx2fc_interface *interface)
{
	/* Dont listen for Ethernet packets anymore */
	__dev_remove_pack(&interface->fcoe_packet_type);
	__dev_remove_pack(&interface->fip_packet_type);
	synchronize_net();
}