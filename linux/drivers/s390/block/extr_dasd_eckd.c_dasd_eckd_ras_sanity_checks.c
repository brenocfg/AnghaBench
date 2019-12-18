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
struct TYPE_3__ {unsigned int trk_per_cyl; } ;
struct dasd_eckd_private {unsigned int real_cyl; TYPE_1__ rdc_data; } ;
struct dasd_device {TYPE_2__* cdev; struct dasd_eckd_private* private; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*,unsigned int) ; 

__attribute__((used)) static int dasd_eckd_ras_sanity_checks(struct dasd_device *device,
				       unsigned int first_trk,
				       unsigned int last_trk)
{
	struct dasd_eckd_private *private = device->private;
	unsigned int trks_per_vol;
	int rc = 0;

	trks_per_vol = private->real_cyl * private->rdc_data.trk_per_cyl;

	if (first_trk >= trks_per_vol) {
		dev_warn(&device->cdev->dev,
			 "Start track number %u used in the space release command is too big\n",
			 first_trk);
		rc = -EINVAL;
	} else if (last_trk >= trks_per_vol) {
		dev_warn(&device->cdev->dev,
			 "Stop track number %u used in the space release command is too big\n",
			 last_trk);
		rc = -EINVAL;
	} else if (first_trk > last_trk) {
		dev_warn(&device->cdev->dev,
			 "Start track %u used in the space release command exceeds the end track\n",
			 first_trk);
		rc = -EINVAL;
	}
	return rc;
}