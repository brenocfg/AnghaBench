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
struct gb_svc_intf_eject_request {int /*<<< orphan*/  intf_id; } ;
struct gb_svc {int /*<<< orphan*/  dev; int /*<<< orphan*/  connection; } ;
typedef  int /*<<< orphan*/  request ;

/* Variables and functions */
 int /*<<< orphan*/  GB_SVC_TYPE_INTF_EJECT ; 
 int /*<<< orphan*/  SVC_INTF_EJECT_TIMEOUT ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int gb_operation_sync_timeout (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct gb_svc_intf_eject_request*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int gb_svc_intf_eject(struct gb_svc *svc, u8 intf_id)
{
	struct gb_svc_intf_eject_request request;
	int ret;

	request.intf_id = intf_id;

	/*
	 * The pulse width for module release in svc is long so we need to
	 * increase the timeout so the operation will not return to soon.
	 */
	ret = gb_operation_sync_timeout(svc->connection,
					GB_SVC_TYPE_INTF_EJECT, &request,
					sizeof(request), NULL, 0,
					SVC_INTF_EJECT_TIMEOUT);
	if (ret) {
		dev_err(&svc->dev, "failed to eject interface %u\n", intf_id);
		return ret;
	}

	return 0;
}