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
struct cpcap_battery_state_data {int dummy; } ;
struct cpcap_battery_ddata {struct cpcap_battery_state_data* state; } ;
typedef  enum cpcap_battery_state { ____Placeholder_cpcap_battery_state } cpcap_battery_state ;

/* Variables and functions */
 int CPCAP_BATTERY_STATE_NR ; 

__attribute__((used)) static struct cpcap_battery_state_data *
cpcap_battery_get_state(struct cpcap_battery_ddata *ddata,
			enum cpcap_battery_state state)
{
	if (state >= CPCAP_BATTERY_STATE_NR)
		return NULL;

	return &ddata->state[state];
}