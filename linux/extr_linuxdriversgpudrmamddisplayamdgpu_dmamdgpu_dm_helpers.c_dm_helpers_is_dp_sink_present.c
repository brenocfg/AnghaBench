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
struct dc_link {struct amdgpu_dm_connector* priv; } ;
struct TYPE_3__ {int /*<<< orphan*/  hw_mutex; } ;
struct TYPE_4__ {TYPE_1__ aux; } ;
struct amdgpu_dm_connector {TYPE_2__ dm_dp_aux; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (char*) ; 
 int dc_link_is_dp_sink_present (struct dc_link*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

bool dm_helpers_is_dp_sink_present(struct dc_link *link)
{
	bool dp_sink_present;
	struct amdgpu_dm_connector *aconnector = link->priv;

	if (!aconnector) {
		BUG_ON("Failed to found connector for link!");
		return true;
	}

	mutex_lock(&aconnector->dm_dp_aux.aux.hw_mutex);
	dp_sink_present = dc_link_is_dp_sink_present(link);
	mutex_unlock(&aconnector->dm_dp_aux.aux.hw_mutex);
	return dp_sink_present;
}