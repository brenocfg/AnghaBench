#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct ti_st_plat_data {int /*<<< orphan*/  (* chip_awake ) (int /*<<< orphan*/ *) ;} ;
struct st_data_s {int ll_state; struct kim_data_s* kim_data; } ;
struct kim_data_s {TYPE_2__* kim_pdev; } ;
struct TYPE_3__ {struct ti_st_plat_data* platform_data; } ;
struct TYPE_4__ {TYPE_1__ dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  LL_WAKE_UP_ACK ; 
#define  ST_LL_ASLEEP 131 
#define  ST_LL_ASLEEP_TO_AWAKE 130 
#define  ST_LL_AWAKE 129 
#define  ST_LL_AWAKE_TO_ASLEEP 128 
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/  send_ll_cmd (struct st_data_s*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ll_device_want_to_wakeup(struct st_data_s *st_data)
{
	struct kim_data_s	*kim_data;
	struct ti_st_plat_data	*pdata;

	/* diff actions in diff states */
	switch (st_data->ll_state) {
	case ST_LL_ASLEEP:
		send_ll_cmd(st_data, LL_WAKE_UP_ACK);	/* send wake_ack */
		break;
	case ST_LL_ASLEEP_TO_AWAKE:
		/* duplicate wake_ind */
		pr_err("duplicate wake_ind while waiting for Wake ack");
		break;
	case ST_LL_AWAKE:
		/* duplicate wake_ind */
		pr_err("duplicate wake_ind already AWAKE");
		break;
	case ST_LL_AWAKE_TO_ASLEEP:
		/* duplicate wake_ind */
		pr_err("duplicate wake_ind");
		break;
	}
	/* update state */
	st_data->ll_state = ST_LL_AWAKE;

	/* communicate to platform about chip wakeup */
	kim_data = st_data->kim_data;
	pdata = kim_data->kim_pdev->dev.platform_data;
	if (pdata->chip_awake)
		pdata->chip_awake(NULL);
}