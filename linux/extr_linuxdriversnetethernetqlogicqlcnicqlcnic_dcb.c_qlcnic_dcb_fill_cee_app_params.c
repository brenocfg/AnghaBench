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
typedef  size_t u8 ;
struct qlcnic_dcb_param {int /*<<< orphan*/ * app; int /*<<< orphan*/ * hdr_prio_pfc_map; } ;
struct qlcnic_dcb_cee {struct qlcnic_dcb_app* app; } ;
struct qlcnic_dcb_app {int valid; size_t priority; int /*<<< orphan*/  protocol; scalar_t__ selector; } ;
struct qlcnic_adapter {TYPE_1__* netdev; } ;
struct dcb_app {size_t priority; int /*<<< orphan*/  protocol; scalar_t__ selector; } ;
struct TYPE_2__ {scalar_t__ dcbnl_ops; } ;

/* Variables and functions */
 int /*<<< orphan*/  QLC_DCB_GET_PROTO_ID_APP (int /*<<< orphan*/ ) ; 
 scalar_t__ QLC_DCB_GET_SELECTOR_APP (int /*<<< orphan*/ ) ; 
 size_t QLC_DCB_MAX_TC ; 
 size_t QLC_DCB_OPER_IDX ; 
 int /*<<< orphan*/  dcb_setapp (TYPE_1__*,struct dcb_app*) ; 
 size_t qlcnic_dcb_get_num_app (struct qlcnic_adapter*,int /*<<< orphan*/ ) ; 
 size_t qlcnic_dcb_get_prio_map_app (struct qlcnic_adapter*,int /*<<< orphan*/ ) ; 
 size_t qlcnic_dcb_prio_count (size_t) ; 

__attribute__((used)) static void
qlcnic_dcb_fill_cee_app_params(struct qlcnic_adapter *adapter, u8 idx,
			       struct qlcnic_dcb_param *each,
			       struct qlcnic_dcb_cee *type)
{
	struct qlcnic_dcb_app *app;
	u8 i, num_app, map, cnt;
	struct dcb_app new_app;

	num_app = qlcnic_dcb_get_num_app(adapter, each->hdr_prio_pfc_map[0]);
	for (i = 0; i < num_app; i++) {
		app = &type->app[i];
		app->valid = true;

		/* Only for CEE (-1) */
		app->selector = QLC_DCB_GET_SELECTOR_APP(each->app[i]) - 1;
		new_app.selector = app->selector;
		app->protocol = QLC_DCB_GET_PROTO_ID_APP(each->app[i]);
		new_app.protocol = app->protocol;
		map = qlcnic_dcb_get_prio_map_app(adapter, each->app[i]);
		cnt = qlcnic_dcb_prio_count(map);

		if (cnt >= QLC_DCB_MAX_TC)
			cnt = 0;

		app->priority = cnt;
		new_app.priority = cnt;

		if (idx == QLC_DCB_OPER_IDX && adapter->netdev->dcbnl_ops)
			dcb_setapp(adapter->netdev, &new_app);
	}
}