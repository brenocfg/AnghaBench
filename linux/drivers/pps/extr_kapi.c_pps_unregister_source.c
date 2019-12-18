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
struct pps_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  pps_kc_remove (struct pps_device*) ; 
 int /*<<< orphan*/  pps_unregister_cdev (struct pps_device*) ; 

void pps_unregister_source(struct pps_device *pps)
{
	pps_kc_remove(pps);
	pps_unregister_cdev(pps);

	/* don't have to kfree(pps) here because it will be done on
	 * device destruction */
}