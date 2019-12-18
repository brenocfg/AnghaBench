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
typedef  void* u8 ;
struct gb_hid_get_report_request {void* report_id; void* report_type; } ;
struct gb_hid {int /*<<< orphan*/  bundle; int /*<<< orphan*/  connection; } ;
typedef  int /*<<< orphan*/  request ;

/* Variables and functions */
 int /*<<< orphan*/  GB_HID_TYPE_GET_REPORT ; 
 int gb_operation_sync (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct gb_hid_get_report_request*,int,unsigned char*,int) ; 
 int gb_pm_runtime_get_sync (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gb_pm_runtime_put_autosuspend (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int gb_hid_get_report(struct gb_hid *ghid, u8 report_type, u8 report_id,
			     unsigned char *buf, int len)
{
	struct gb_hid_get_report_request request;
	int ret;

	ret = gb_pm_runtime_get_sync(ghid->bundle);
	if (ret)
		return ret;

	request.report_type = report_type;
	request.report_id = report_id;

	ret = gb_operation_sync(ghid->connection, GB_HID_TYPE_GET_REPORT,
				&request, sizeof(request), buf, len);

	gb_pm_runtime_put_autosuspend(ghid->bundle);

	return ret;
}