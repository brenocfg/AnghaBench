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
struct dasd_device {TYPE_2__* cdev; int /*<<< orphan*/  flags; TYPE_1__* block; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;
struct TYPE_3__ {int /*<<< orphan*/  bp_block; } ;

/* Variables and functions */
 int /*<<< orphan*/  DASD_FLAG_DEVICE_RO ; 
 int /*<<< orphan*/  dev_name (int /*<<< orphan*/ *) ; 
 int mdsk_init_io (struct dasd_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mdsk_term_io (struct dasd_device*) ; 
 int /*<<< orphan*/  pr_warn (char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  test_and_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
dasd_diag_erp(struct dasd_device *device)
{
	int rc;

	mdsk_term_io(device);
	rc = mdsk_init_io(device, device->block->bp_block, 0, NULL);
	if (rc == 4) {
		if (!(test_and_set_bit(DASD_FLAG_DEVICE_RO, &device->flags)))
			pr_warn("%s: The access mode of a DIAG device changed to read-only\n",
				dev_name(&device->cdev->dev));
		rc = 0;
	}
	if (rc)
		pr_warn("%s: DIAG ERP failed with rc=%d\n",
			dev_name(&device->cdev->dev), rc);
}