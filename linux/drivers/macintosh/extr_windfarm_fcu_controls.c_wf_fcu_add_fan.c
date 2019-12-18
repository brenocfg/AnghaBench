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
struct wf_fcu_priv {int /*<<< orphan*/  ref; int /*<<< orphan*/  fan_list; } ;
struct TYPE_2__ {char const* name; int /*<<< orphan*/ * ops; int /*<<< orphan*/  type; struct wf_fcu_fan* priv; } ;
struct wf_fcu_fan {int id; int min; int max; int /*<<< orphan*/  link; TYPE_1__ ctrl; struct wf_fcu_priv* fcu_priv; } ;

/* Variables and functions */
 int FCU_FAN_RPM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  WF_CONTROL_PWM_FAN ; 
 int /*<<< orphan*/  WF_CONTROL_RPM_FAN ; 
 int /*<<< orphan*/  kfree (struct wf_fcu_fan*) ; 
 int /*<<< orphan*/  kref_get (int /*<<< orphan*/ *) ; 
 struct wf_fcu_fan* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_err (char*,char const*) ; 
 int /*<<< orphan*/  strlen (char*) ; 
 int /*<<< orphan*/  strncmp (char const*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wf_fcu_fan_pwm_ops ; 
 int /*<<< orphan*/  wf_fcu_fan_rpm_ops ; 
 int /*<<< orphan*/  wf_fcu_get_pump_minmax (struct wf_fcu_fan*) ; 
 int /*<<< orphan*/  wf_fcu_get_rpmfan_minmax (struct wf_fcu_fan*) ; 
 scalar_t__ wf_register_control (TYPE_1__*) ; 

__attribute__((used)) static void wf_fcu_add_fan(struct wf_fcu_priv *pv, const char *name,
			   int type, int id)
{
	struct wf_fcu_fan *fan;

	fan = kzalloc(sizeof(*fan), GFP_KERNEL);
	if (!fan)
		return;
	fan->fcu_priv = pv;
	fan->id = id;
	fan->ctrl.name = name;
	fan->ctrl.priv = fan;

	/* min/max is oddball but the code comes from
	 * therm_pm72 which seems to work so ...
	 */
	if (type == FCU_FAN_RPM) {
		if (!strncmp(name, "cpu-pump", strlen("cpu-pump")))
			wf_fcu_get_pump_minmax(fan);
		else
			wf_fcu_get_rpmfan_minmax(fan);
		fan->ctrl.type = WF_CONTROL_RPM_FAN;
		fan->ctrl.ops = &wf_fcu_fan_rpm_ops;
	} else {
		fan->min = 10;
		fan->max = 100;
		fan->ctrl.type = WF_CONTROL_PWM_FAN;
		fan->ctrl.ops = &wf_fcu_fan_pwm_ops;
	}

	if (wf_register_control(&fan->ctrl)) {
		pr_err("wf_fcu: Failed to register fan %s\n", name);
		kfree(fan);
		return;
	}
	list_add(&fan->link, &pv->fan_list);
	kref_get(&pv->ref);
}