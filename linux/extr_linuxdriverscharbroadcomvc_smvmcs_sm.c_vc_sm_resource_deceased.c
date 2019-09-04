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
struct sm_resource_t {scalar_t__* res_stats; } ;
struct TYPE_2__ {int /*<<< orphan*/ * deceased; int /*<<< orphan*/ * terminated; int /*<<< orphan*/  res_deceased_cnt; int /*<<< orphan*/  res_terminated_cnt; } ;

/* Variables and functions */
 int END_ALL ; 
 TYPE_1__* sm_state ; 

__attribute__((used)) static void vc_sm_resource_deceased(struct sm_resource_t *p_res, int terminated)
{
	if (sm_state != NULL) {
		if (p_res != NULL) {
			int ix;

			if (terminated)
				sm_state->res_terminated_cnt++;
			else
				sm_state->res_deceased_cnt++;

			for (ix = 0; ix < END_ALL; ix++) {
				if (terminated)
					sm_state->terminated[ix] +=
					    p_res->res_stats[ix];
				else
					sm_state->deceased[ix] +=
					    p_res->res_stats[ix];
			}
		}
	}
}