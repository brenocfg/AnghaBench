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
struct mqd_manager {int dummy; } ;
struct TYPE_2__ {struct mqd_manager* (* mqd_manager_init ) (int,int /*<<< orphan*/ ) ;} ;
struct device_queue_manager {struct mqd_manager** mqd_mgrs; int /*<<< orphan*/  dev; TYPE_1__ asic_ops; } ;

/* Variables and functions */
 int ENOMEM ; 
 int KFD_MQD_TYPE_MAX ; 
 int /*<<< orphan*/  kfree (struct mqd_manager*) ; 
 int /*<<< orphan*/  pr_err (char*,int) ; 
 struct mqd_manager* stub1 (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int init_mqd_managers(struct device_queue_manager *dqm)
{
	int i, j;
	struct mqd_manager *mqd_mgr;

	for (i = 0; i < KFD_MQD_TYPE_MAX; i++) {
		mqd_mgr = dqm->asic_ops.mqd_manager_init(i, dqm->dev);
		if (!mqd_mgr) {
			pr_err("mqd manager [%d] initialization failed\n", i);
			goto out_free;
		}
		dqm->mqd_mgrs[i] = mqd_mgr;
	}

	return 0;

out_free:
	for (j = 0; j < i; j++) {
		kfree(dqm->mqd_mgrs[j]);
		dqm->mqd_mgrs[j] = NULL;
	}

	return -ENOMEM;
}