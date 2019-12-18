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
struct megasas_instance {int /*<<< orphan*/  clusterId; scalar_t__ peerIsPresent; scalar_t__ requestorId; } ;
struct TYPE_2__ {struct megasas_instance** instance; } ;

/* Variables and functions */
 int MAX_MGMT_ADAPTERS ; 
 int /*<<< orphan*/  MEGASAS_CLUSTER_ID_SIZE ; 
 TYPE_1__ megasas_mgmt_info ; 
 scalar_t__ memcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct
megasas_instance *megasas_get_peer_instance(struct megasas_instance *instance)
{
	int i;

	for (i = 0; i < MAX_MGMT_ADAPTERS; i++) {
		if (megasas_mgmt_info.instance[i] &&
			(megasas_mgmt_info.instance[i] != instance) &&
			 megasas_mgmt_info.instance[i]->requestorId &&
			 megasas_mgmt_info.instance[i]->peerIsPresent &&
			(memcmp((megasas_mgmt_info.instance[i]->clusterId),
			instance->clusterId, MEGASAS_CLUSTER_ID_SIZE) == 0))
			return megasas_mgmt_info.instance[i];
	}
	return NULL;
}