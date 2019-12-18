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
struct intel_guc_client {int /*<<< orphan*/  stage_id; int /*<<< orphan*/  guc; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  GEM_BUG_ON (int) ; 
 int /*<<< orphan*/  GUC_DOORBELL_INVALID ; 
 int /*<<< orphan*/  __fini_doorbell (struct intel_guc_client*) ; 
 int __guc_deallocate_doorbell (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __update_doorbell_desc (struct intel_guc_client*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  has_doorbell (struct intel_guc_client*) ; 

__attribute__((used)) static int destroy_doorbell(struct intel_guc_client *client)
{
	int ret;

	GEM_BUG_ON(!has_doorbell(client));

	__fini_doorbell(client);
	ret = __guc_deallocate_doorbell(client->guc, client->stage_id);
	if (ret)
		DRM_ERROR("Couldn't destroy client %u doorbell: %d\n",
			  client->stage_id, ret);

	__update_doorbell_desc(client, GUC_DOORBELL_INVALID);

	return ret;
}