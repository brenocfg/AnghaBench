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
struct ib_mad_mgmt_method_table {struct ib_mad_agent_private** agent; } ;
struct ib_mad_agent_private {int dummy; } ;

/* Variables and functions */
 int IB_MGMT_MAX_METHODS ; 

__attribute__((used)) static void remove_methods_mad_agent(struct ib_mad_mgmt_method_table *method,
				     struct ib_mad_agent_private *agent)
{
	int i;

	/* Remove any methods for this mad agent */
	for (i = 0; i < IB_MGMT_MAX_METHODS; i++) {
		if (method->agent[i] == agent) {
			method->agent[i] = NULL;
		}
	}
}