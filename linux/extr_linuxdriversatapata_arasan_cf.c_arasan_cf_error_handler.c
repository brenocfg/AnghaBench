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
struct ata_port {TYPE_1__* host; } ;
struct arasan_cf_dev {int /*<<< orphan*/  dwork; int /*<<< orphan*/  work; } ;
struct TYPE_2__ {struct arasan_cf_dev* private_data; } ;

/* Variables and functions */
 void ata_sff_error_handler (struct ata_port*) ; 
 int /*<<< orphan*/  cancel_delayed_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cancel_work_sync (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void arasan_cf_error_handler(struct ata_port *ap)
{
	struct arasan_cf_dev *acdev = ap->host->private_data;

	/*
	 * DMA transfers using an external DMA controller may be scheduled.
	 * Abort them before handling error. Refer data_xfer() for further
	 * details.
	 */
	cancel_work_sync(&acdev->work);
	cancel_delayed_work_sync(&acdev->dwork);
	return ata_sff_error_handler(ap);
}