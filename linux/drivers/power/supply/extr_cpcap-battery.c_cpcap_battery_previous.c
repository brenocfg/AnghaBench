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
struct cpcap_battery_ddata {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CPCAP_BATTERY_STATE_PREVIOUS ; 
 struct cpcap_battery_state_data* cpcap_battery_get_state (struct cpcap_battery_ddata*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct cpcap_battery_state_data *
cpcap_battery_previous(struct cpcap_battery_ddata *ddata)
{
	return cpcap_battery_get_state(ddata, CPCAP_BATTERY_STATE_PREVIOUS);
}