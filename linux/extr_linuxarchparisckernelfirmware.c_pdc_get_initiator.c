#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct pdc_initiator {int host_id; int factor; int width; int mode; } ;
typedef  int hardware_path ;
struct TYPE_3__ {int /*<<< orphan*/  sys_model_name; } ;
struct TYPE_4__ {TYPE_1__ pdc; } ;

/* Variables and functions */
 int /*<<< orphan*/  PDC_GET_INITIATOR ; 
 int /*<<< orphan*/  PDC_INITIATOR ; 
 int PDC_OK ; 
 int /*<<< orphan*/  __pa (int*) ; 
 TYPE_2__ boot_cpu_data ; 
 int mem_pdc_call (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pdc_lock ; 
 int* pdc_result ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int strlen (int /*<<< orphan*/ ) ; 
 scalar_t__ strncmp (int /*<<< orphan*/ ,char*,int) ; 

int pdc_get_initiator(struct hardware_path *hwpath, struct pdc_initiator *initiator)
{
	int retval;
	unsigned long flags;

	spin_lock_irqsave(&pdc_lock, flags);

/* BCJ-XXXX series boxes. E.G. "9000/785/C3000" */
#define IS_SPROCKETS() (strlen(boot_cpu_data.pdc.sys_model_name) == 14 && \
	strncmp(boot_cpu_data.pdc.sys_model_name, "9000/785", 8) == 0)

	retval = mem_pdc_call(PDC_INITIATOR, PDC_GET_INITIATOR, 
			      __pa(pdc_result), __pa(hwpath));
	if (retval < PDC_OK)
		goto out;

	if (pdc_result[0] < 16) {
		initiator->host_id = pdc_result[0];
	} else {
		initiator->host_id = -1;
	}

	/*
	 * Sprockets and Piranha return 20 or 40 (MT/s).  Prelude returns
	 * 1, 2, 5 or 10 for 5, 10, 20 or 40 MT/s, respectively
	 */
	switch (pdc_result[1]) {
		case  1: initiator->factor = 50; break;
		case  2: initiator->factor = 25; break;
		case  5: initiator->factor = 12; break;
		case 25: initiator->factor = 10; break;
		case 20: initiator->factor = 12; break;
		case 40: initiator->factor = 10; break;
		default: initiator->factor = -1; break;
	}

	if (IS_SPROCKETS()) {
		initiator->width = pdc_result[4];
		initiator->mode = pdc_result[5];
	} else {
		initiator->width = -1;
		initiator->mode = -1;
	}

 out:
	spin_unlock_irqrestore(&pdc_lock, flags);

	return (retval >= PDC_OK);
}