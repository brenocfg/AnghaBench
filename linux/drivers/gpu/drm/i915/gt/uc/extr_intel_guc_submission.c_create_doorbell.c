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
struct intel_guc_client {int /*<<< orphan*/  stage_id; int /*<<< orphan*/  guc; int /*<<< orphan*/  doorbell_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG_DRIVER (char*,int /*<<< orphan*/ ,int) ; 
 int ENODEV ; 
 int /*<<< orphan*/  GUC_DOORBELL_INVALID ; 
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  __fini_doorbell (struct intel_guc_client*) ; 
 int __guc_allocate_doorbell (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __init_doorbell (struct intel_guc_client*) ; 
 int /*<<< orphan*/  __update_doorbell_desc (struct intel_guc_client*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  has_doorbell (struct intel_guc_client*) ; 

__attribute__((used)) static int create_doorbell(struct intel_guc_client *client)
{
	int ret;

	if (WARN_ON(!has_doorbell(client)))
		return -ENODEV; /* internal setup error, should never happen */

	__update_doorbell_desc(client, client->doorbell_id);
	__init_doorbell(client);

	ret = __guc_allocate_doorbell(client->guc, client->stage_id);
	if (ret) {
		__fini_doorbell(client);
		__update_doorbell_desc(client, GUC_DOORBELL_INVALID);
		DRM_DEBUG_DRIVER("Couldn't create client %u doorbell: %d\n",
				 client->stage_id, ret);
		return ret;
	}

	return 0;
}