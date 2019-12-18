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
struct aac_dev {TYPE_1__** hba_map; } ;
struct aac_ciss_identify_pd {int current_queue_depth_limit; } ;
struct TYPE_2__ {scalar_t__ devtype; int qd_limit; struct aac_ciss_identify_pd* safw_identify_resp; } ;

/* Variables and functions */
 scalar_t__ AAC_DEVTYPE_NATIVE_RAW ; 

__attribute__((used)) static void aac_set_safw_target_qd(struct aac_dev *dev, int bus, int target)
{

	struct aac_ciss_identify_pd *identify_resp;

	if (dev->hba_map[bus][target].devtype != AAC_DEVTYPE_NATIVE_RAW)
		return;

	identify_resp = dev->hba_map[bus][target].safw_identify_resp;
	if (identify_resp == NULL) {
		dev->hba_map[bus][target].qd_limit = 32;
		return;
	}

	if (identify_resp->current_queue_depth_limit <= 0 ||
		identify_resp->current_queue_depth_limit > 255)
		dev->hba_map[bus][target].qd_limit = 32;
	else
		dev->hba_map[bus][target].qd_limit =
			identify_resp->current_queue_depth_limit;
}