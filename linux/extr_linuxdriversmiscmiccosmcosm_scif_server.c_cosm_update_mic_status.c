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
struct cosm_device {scalar_t__ shutdown_status_int; } ;

/* Variables and functions */
 scalar_t__ MIC_NOP ; 
 int /*<<< orphan*/  cosm_set_shutdown_status (struct cosm_device*,scalar_t__) ; 

__attribute__((used)) static void cosm_update_mic_status(struct cosm_device *cdev)
{
	if (cdev->shutdown_status_int != MIC_NOP) {
		cosm_set_shutdown_status(cdev, cdev->shutdown_status_int);
		cdev->shutdown_status_int = MIC_NOP;
	}
}