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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u16 ;
struct gb_host_device {int /*<<< orphan*/  dev; } ;
struct gb_connection {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,size_t) ; 
 struct gb_connection* gb_connection_hd_find (struct gb_host_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gb_connection_put (struct gb_connection*) ; 
 int /*<<< orphan*/  gb_connection_recv (struct gb_connection*,int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  trace_gb_hd_in (struct gb_host_device*) ; 

void greybus_data_rcvd(struct gb_host_device *hd, u16 cport_id,
		       u8 *data, size_t length)
{
	struct gb_connection *connection;

	trace_gb_hd_in(hd);

	connection = gb_connection_hd_find(hd, cport_id);
	if (!connection) {
		dev_err(&hd->dev,
			"nonexistent connection (%zu bytes dropped)\n", length);
		return;
	}
	gb_connection_recv(connection, data, length);
	gb_connection_put(connection);
}