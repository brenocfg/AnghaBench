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
typedef  int u8 ;
typedef  int u16 ;
struct gb_connection {int hd_cport_id; int intf_cport_id; int /*<<< orphan*/  name; TYPE_1__* intf; } ;
struct TYPE_2__ {int interface_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int,char*,int,int,int) ; 

__attribute__((used)) static void gb_connection_init_name(struct gb_connection *connection)
{
	u16 hd_cport_id = connection->hd_cport_id;
	u16 cport_id = 0;
	u8 intf_id = 0;

	if (connection->intf) {
		intf_id = connection->intf->interface_id;
		cport_id = connection->intf_cport_id;
	}

	snprintf(connection->name, sizeof(connection->name),
		 "%u/%u:%u", hd_cport_id, intf_id, cport_id);
}