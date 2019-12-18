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
struct gb_operation_msg_hdr {int dummy; } ;
struct gb_host_device {int /*<<< orphan*/  dev; TYPE_1__* driver; } ;
struct gb_cport_shutdown_request {int dummy; } ;
struct gb_connection {int /*<<< orphan*/  name; int /*<<< orphan*/  hd_cport_id; scalar_t__ mode_switch; struct gb_host_device* hd; } ;
struct TYPE_2__ {int (* cport_quiesce ) (struct gb_host_device*,int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  GB_CONNECTION_CPORT_QUIESCE_TIMEOUT ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int) ; 
 int stub1 (struct gb_host_device*,int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int gb_connection_hd_cport_quiesce(struct gb_connection *connection)
{
	struct gb_host_device *hd = connection->hd;
	size_t peer_space;
	int ret;

	if (!hd->driver->cport_quiesce)
		return 0;

	peer_space = sizeof(struct gb_operation_msg_hdr) +
			sizeof(struct gb_cport_shutdown_request);

	if (connection->mode_switch)
		peer_space += sizeof(struct gb_operation_msg_hdr);

	if (!hd->driver->cport_quiesce)
		return 0;

	ret = hd->driver->cport_quiesce(hd, connection->hd_cport_id,
					peer_space,
					GB_CONNECTION_CPORT_QUIESCE_TIMEOUT);
	if (ret) {
		dev_err(&hd->dev, "%s: failed to quiesce host cport: %d\n",
			connection->name, ret);
		return ret;
	}

	return 0;
}