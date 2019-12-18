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
struct cpcap_charger_ddata {int /*<<< orphan*/ * gpio; } ;

/* Variables and functions */
 int /*<<< orphan*/  gpiod_set_value (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void cpcap_charger_set_inductive_path(struct cpcap_charger_ddata *ddata,
					     bool enabled)
{
	if (!ddata->gpio[1])
		return;

	gpiod_set_value(ddata->gpio[1], enabled);
}