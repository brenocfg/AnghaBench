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
struct gb_svc {int /*<<< orphan*/  dev; int /*<<< orphan*/  ap_intf_id; } ;
struct gb_operation {struct gb_connection* connection; } ;
struct gb_connection {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GB_SVC_NO_DE_EMPHASIS ; 
 int /*<<< orphan*/  GB_SVC_SMALL_AMPLITUDE ; 
 int /*<<< orphan*/  GB_SVC_UNIPRO_HS_SERIES_A ; 
 int /*<<< orphan*/  GB_SVC_UNIPRO_SLOW_AUTO_MODE ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*,int) ; 
 struct gb_svc* gb_connection_get_data (struct gb_connection*) ; 
 int gb_svc_intf_set_power_mode (struct gb_svc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void gb_svc_process_hello_deferred(struct gb_operation *operation)
{
	struct gb_connection *connection = operation->connection;
	struct gb_svc *svc = gb_connection_get_data(connection);
	int ret;

	/*
	 * XXX This is a hack/work-around to reconfigure the APBridgeA-Switch
	 * link to PWM G2, 1 Lane, Slow Auto, so that it has sufficient
	 * bandwidth for 3 audio streams plus boot-over-UniPro of a hot-plugged
	 * module.
	 *
	 * The code should be removed once SW-2217, Heuristic for UniPro
	 * Power Mode Changes is resolved.
	 */
	ret = gb_svc_intf_set_power_mode(svc, svc->ap_intf_id,
					 GB_SVC_UNIPRO_HS_SERIES_A,
					 GB_SVC_UNIPRO_SLOW_AUTO_MODE,
					 2, 1,
					 GB_SVC_SMALL_AMPLITUDE,
					 GB_SVC_NO_DE_EMPHASIS,
					 GB_SVC_UNIPRO_SLOW_AUTO_MODE,
					 2, 1,
					 0, 0,
					 NULL, NULL);

	if (ret)
		dev_warn(&svc->dev,
			 "power mode change failed on AP to switch link: %d\n",
			 ret);
}