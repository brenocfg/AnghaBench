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
struct ptp_pin_desc {int func; unsigned int chan; } ;
struct ptp_clock {int /*<<< orphan*/  pincfg_mux; TYPE_1__* info; } ;
typedef  enum ptp_pin_function { ____Placeholder_ptp_pin_function } ptp_pin_function ;
struct TYPE_2__ {int n_pins; struct ptp_pin_desc* pin_config; } ;

/* Variables and functions */
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

int ptp_find_pin(struct ptp_clock *ptp,
		 enum ptp_pin_function func, unsigned int chan)
{
	struct ptp_pin_desc *pin = NULL;
	int i;

	mutex_lock(&ptp->pincfg_mux);
	for (i = 0; i < ptp->info->n_pins; i++) {
		if (ptp->info->pin_config[i].func == func &&
		    ptp->info->pin_config[i].chan == chan) {
			pin = &ptp->info->pin_config[i];
			break;
		}
	}
	mutex_unlock(&ptp->pincfg_mux);

	return pin ? i : -1;
}