#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct hnae3_handle {TYPE_3__* pdev; TYPE_2__* ae_algo; } ;
struct TYPE_6__ {int /*<<< orphan*/  dev; } ;
struct TYPE_5__ {TYPE_1__* ops; } ;
struct TYPE_4__ {int (* set_channels ) (struct hnae3_handle*,int /*<<< orphan*/ ,int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  HNAE3_INIT_CLIENT ; 
 int /*<<< orphan*/  HNAE3_UNINIT_CLIENT ; 
 int /*<<< orphan*/  HNAE3_UP_CLIENT ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int hns3_reset_notify (struct hnae3_handle*,int /*<<< orphan*/ ) ; 
 int stub1 (struct hnae3_handle*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int hns3_change_channels(struct hnae3_handle *handle, u32 new_tqp_num,
				bool rxfh_configured)
{
	int ret;

	ret = handle->ae_algo->ops->set_channels(handle, new_tqp_num,
						 rxfh_configured);
	if (ret) {
		dev_err(&handle->pdev->dev,
			"Change tqp num(%u) fail.\n", new_tqp_num);
		return ret;
	}

	ret = hns3_reset_notify(handle, HNAE3_INIT_CLIENT);
	if (ret)
		return ret;

	ret =  hns3_reset_notify(handle, HNAE3_UP_CLIENT);
	if (ret)
		hns3_reset_notify(handle, HNAE3_UNINIT_CLIENT);

	return ret;
}