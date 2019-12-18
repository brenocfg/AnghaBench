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
struct gb_svc_pwrmon_rail_count_get_response {int /*<<< orphan*/  rail_count; } ;
struct gb_svc {int /*<<< orphan*/  dev; int /*<<< orphan*/  connection; } ;
typedef  int /*<<< orphan*/  response ;

/* Variables and functions */
 int /*<<< orphan*/  GB_SVC_TYPE_PWRMON_RAIL_COUNT_GET ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 int gb_operation_sync (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct gb_svc_pwrmon_rail_count_get_response*,int) ; 

__attribute__((used)) static int gb_svc_pwrmon_rail_count_get(struct gb_svc *svc, u8 *value)
{
	struct gb_svc_pwrmon_rail_count_get_response response;
	int ret;

	ret = gb_operation_sync(svc->connection,
				GB_SVC_TYPE_PWRMON_RAIL_COUNT_GET, NULL, 0,
				&response, sizeof(response));
	if (ret) {
		dev_err(&svc->dev, "failed to get rail count: %d\n", ret);
		return ret;
	}

	*value = response.rail_count;

	return 0;
}