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
struct megasas_pd_list {int dummy; } ;
struct megasas_instance {TYPE_1__* pdev; scalar_t__ enable_fw_dev_list; int /*<<< orphan*/  ld_ids; int /*<<< orphan*/  pd_list; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int FAILED ; 
 int MEGASAS_MAX_LD_IDS ; 
 int MEGASAS_MAX_PD ; 
 int /*<<< orphan*/  MR_LD_QUERY_TYPE_EXPOSED_TO_HOST ; 
 int SUCCESS ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ megasas_get_pd_list (struct megasas_instance*) ; 
 scalar_t__ megasas_host_device_list_query (struct megasas_instance*,int) ; 
 scalar_t__ megasas_ld_list_query (struct megasas_instance*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static
int megasas_get_device_list(struct megasas_instance *instance)
{
	memset(instance->pd_list, 0,
	       (MEGASAS_MAX_PD * sizeof(struct megasas_pd_list)));
	memset(instance->ld_ids, 0xff, MEGASAS_MAX_LD_IDS);

	if (instance->enable_fw_dev_list) {
		if (megasas_host_device_list_query(instance, true))
			return FAILED;
	} else {
		if (megasas_get_pd_list(instance) < 0) {
			dev_err(&instance->pdev->dev, "failed to get PD list\n");
			return FAILED;
		}

		if (megasas_ld_list_query(instance,
					  MR_LD_QUERY_TYPE_EXPOSED_TO_HOST)) {
			dev_err(&instance->pdev->dev, "failed to get LD list\n");
			return FAILED;
		}
	}

	return SUCCESS;
}