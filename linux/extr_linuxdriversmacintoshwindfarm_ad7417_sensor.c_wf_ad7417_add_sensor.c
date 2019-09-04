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
struct wf_sensor_ops {int dummy; } ;
struct wf_ad7417_priv {int /*<<< orphan*/  ref; TYPE_1__* sensors; int /*<<< orphan*/  cpu; } ;
struct TYPE_2__ {struct wf_sensor_ops const* ops; struct wf_ad7417_priv* priv; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  kasprintf (int /*<<< orphan*/ ,char*,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kref_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wf_register_sensor (TYPE_1__*) ; 

__attribute__((used)) static void wf_ad7417_add_sensor(struct wf_ad7417_priv *pv,
				 int index, const char *name,
				 const struct wf_sensor_ops *ops)
{
	pv->sensors[index].name = kasprintf(GFP_KERNEL, "%s-%d", name, pv->cpu);
	pv->sensors[index].priv = pv;
	pv->sensors[index].ops = ops;
	if (!wf_register_sensor(&pv->sensors[index]))
		kref_get(&pv->ref);
}