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
struct se_device {int dev_reservation_flags; scalar_t__ dev_res_bin_isid; int /*<<< orphan*/ * reservation_holder; } ;

/* Variables and functions */
 int DRF_SPC2_RESERVATIONS ; 
 int DRF_SPC2_RESERVATIONS_WITH_ISID ; 

void target_release_reservation(struct se_device *dev)
{
	dev->reservation_holder = NULL;
	dev->dev_reservation_flags &= ~DRF_SPC2_RESERVATIONS;
	if (dev->dev_reservation_flags & DRF_SPC2_RESERVATIONS_WITH_ISID) {
		dev->dev_res_bin_isid = 0;
		dev->dev_reservation_flags &= ~DRF_SPC2_RESERVATIONS_WITH_ISID;
	}
}