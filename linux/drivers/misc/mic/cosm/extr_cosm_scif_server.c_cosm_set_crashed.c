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
struct cosm_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  MIC_CRASHED ; 
 int /*<<< orphan*/  cosm_shutdown_status_int (struct cosm_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cosm_update_mic_status (struct cosm_device*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static void cosm_set_crashed(struct cosm_device *cdev)
{
	dev_err(&cdev->dev, "node alive timeout\n");
	cosm_shutdown_status_int(cdev, MIC_CRASHED);
	cosm_update_mic_status(cdev);
}