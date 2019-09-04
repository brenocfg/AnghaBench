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
struct mqd_manager {int dummy; } ;
struct device_queue_manager {struct mqd_manager** mqd_mgrs; int /*<<< orphan*/  dev; } ;
typedef  enum KFD_MQD_TYPE { ____Placeholder_KFD_MQD_TYPE } KFD_MQD_TYPE ;

/* Variables and functions */
 int KFD_MQD_TYPE_MAX ; 
 scalar_t__ WARN_ON (int) ; 
 struct mqd_manager* mqd_manager_init (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_debug (char*,int) ; 
 int /*<<< orphan*/  pr_err (char*) ; 

__attribute__((used)) static struct mqd_manager *get_mqd_manager(
		struct device_queue_manager *dqm, enum KFD_MQD_TYPE type)
{
	struct mqd_manager *mqd_mgr;

	if (WARN_ON(type >= KFD_MQD_TYPE_MAX))
		return NULL;

	pr_debug("mqd type %d\n", type);

	mqd_mgr = dqm->mqd_mgrs[type];
	if (!mqd_mgr) {
		mqd_mgr = mqd_manager_init(type, dqm->dev);
		if (!mqd_mgr)
			pr_err("mqd manager is NULL");
		dqm->mqd_mgrs[type] = mqd_mgr;
	}

	return mqd_mgr;
}