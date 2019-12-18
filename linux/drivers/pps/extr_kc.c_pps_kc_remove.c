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
struct pps_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ ,char*) ; 
 struct pps_device* pps_kc_hardpps_dev ; 
 int /*<<< orphan*/  pps_kc_hardpps_lock ; 
 scalar_t__ pps_kc_hardpps_mode ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

void pps_kc_remove(struct pps_device *pps)
{
	spin_lock_irq(&pps_kc_hardpps_lock);
	if (pps == pps_kc_hardpps_dev) {
		pps_kc_hardpps_mode = 0;
		pps_kc_hardpps_dev = NULL;
		spin_unlock_irq(&pps_kc_hardpps_lock);
		dev_info(pps->dev, "unbound kernel consumer"
				" on device removal\n");
	} else
		spin_unlock_irq(&pps_kc_hardpps_lock);
}