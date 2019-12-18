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
struct gb_interface {int /*<<< orphan*/  interface_id; } ;
struct gb_host_device {int /*<<< orphan*/  dev; TYPE_1__* svc; } ;
struct gb_connection {int /*<<< orphan*/  name; struct gb_host_device* hd; int /*<<< orphan*/  intf_cport_id; int /*<<< orphan*/  hd_cport_id; struct gb_interface* intf; } ;
struct TYPE_2__ {int /*<<< orphan*/  ap_intf_id; } ;

/* Variables and functions */
 int GB_SVC_CPORT_FLAG_CSD_N ; 
 int GB_SVC_CPORT_FLAG_CSV_N ; 
 int GB_SVC_CPORT_FLAG_E2EFC ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ gb_connection_e2efc_enabled (struct gb_connection*) ; 
 scalar_t__ gb_connection_flow_control_disabled (struct gb_connection*) ; 
 scalar_t__ gb_connection_is_static (struct gb_connection*) ; 
 int gb_svc_connection_create (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
gb_connection_svc_connection_create(struct gb_connection *connection)
{
	struct gb_host_device *hd = connection->hd;
	struct gb_interface *intf;
	u8 cport_flags;
	int ret;

	if (gb_connection_is_static(connection))
		return 0;

	intf = connection->intf;

	/*
	 * Enable either E2EFC or CSD, unless no flow control is requested.
	 */
	cport_flags = GB_SVC_CPORT_FLAG_CSV_N;
	if (gb_connection_flow_control_disabled(connection)) {
		cport_flags |= GB_SVC_CPORT_FLAG_CSD_N;
	} else if (gb_connection_e2efc_enabled(connection)) {
		cport_flags |= GB_SVC_CPORT_FLAG_CSD_N |
				GB_SVC_CPORT_FLAG_E2EFC;
	}

	ret = gb_svc_connection_create(hd->svc,
				       hd->svc->ap_intf_id,
				       connection->hd_cport_id,
				       intf->interface_id,
				       connection->intf_cport_id,
				       cport_flags);
	if (ret) {
		dev_err(&connection->hd->dev,
			"%s: failed to create svc connection: %d\n",
			connection->name, ret);
		return ret;
	}

	return 0;
}