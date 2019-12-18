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
struct cpcap_battery_state_data {int /*<<< orphan*/  temperature; int /*<<< orphan*/  cc; int /*<<< orphan*/  counter_uah; int /*<<< orphan*/  current_ua; int /*<<< orphan*/  voltage; int /*<<< orphan*/  time; } ;
struct cpcap_battery_ddata {int dummy; } ;
typedef  int /*<<< orphan*/  state ;
typedef  scalar_t__ s64 ;
typedef  int /*<<< orphan*/  ktime_t ;

/* Variables and functions */
 scalar_t__ CPCAP_BATTERY_CC_SAMPLE_PERIOD_MS ; 
 int /*<<< orphan*/  cpcap_battery_get_current (struct cpcap_battery_ddata*) ; 
 int /*<<< orphan*/  cpcap_battery_get_voltage (struct cpcap_battery_ddata*) ; 
 struct cpcap_battery_state_data* cpcap_battery_latest (struct cpcap_battery_ddata*) ; 
 struct cpcap_battery_state_data* cpcap_battery_previous (struct cpcap_battery_ddata*) ; 
 int /*<<< orphan*/  cpcap_battery_read_accumulated (struct cpcap_battery_ddata*,int /*<<< orphan*/ *) ; 
 int cpcap_charger_battery_temperature (struct cpcap_battery_ddata*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ktime_get () ; 
 int /*<<< orphan*/  ktime_sub (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ ktime_to_ms (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (struct cpcap_battery_state_data*,struct cpcap_battery_state_data*,int) ; 
 int /*<<< orphan*/  memset (struct cpcap_battery_state_data*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int cpcap_battery_update_status(struct cpcap_battery_ddata *ddata)
{
	struct cpcap_battery_state_data state, *latest, *previous;
	ktime_t now;
	int error;

	memset(&state, 0, sizeof(state));
	now = ktime_get();

	latest = cpcap_battery_latest(ddata);
	if (latest) {
		s64 delta_ms = ktime_to_ms(ktime_sub(now, latest->time));

		if (delta_ms < CPCAP_BATTERY_CC_SAMPLE_PERIOD_MS)
			return delta_ms;
	}

	state.time = now;
	state.voltage = cpcap_battery_get_voltage(ddata);
	state.current_ua = cpcap_battery_get_current(ddata);
	state.counter_uah = cpcap_battery_read_accumulated(ddata, &state.cc);

	error = cpcap_charger_battery_temperature(ddata,
						  &state.temperature);
	if (error)
		return error;

	previous = cpcap_battery_previous(ddata);
	memcpy(previous, latest, sizeof(*previous));
	memcpy(latest, &state, sizeof(*latest));

	return 0;
}