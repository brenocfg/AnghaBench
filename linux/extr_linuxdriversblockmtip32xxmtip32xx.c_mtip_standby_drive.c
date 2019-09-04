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
struct driver_data {TYPE_1__* pdev; TYPE_2__* port; int /*<<< orphan*/  dd_flag; scalar_t__ sr; } ;
struct TYPE_4__ {int /*<<< orphan*/  flags; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  MTIP_DDF_REBUILD_FAILED_BIT ; 
 int /*<<< orphan*/  MTIP_DDF_SEC_LOCK_BIT ; 
 int /*<<< orphan*/  MTIP_PF_REBUILD_BIT ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*) ; 
 int mtip_standby_immediate (TYPE_2__*) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int mtip_standby_drive(struct driver_data *dd)
{
	int rv = 0;

	if (dd->sr || !dd->port)
		return -ENODEV;
	/*
	 * Send standby immediate (E0h) to the drive so that it
	 * saves its state.
	 */
	if (!test_bit(MTIP_PF_REBUILD_BIT, &dd->port->flags) &&
	    !test_bit(MTIP_DDF_REBUILD_FAILED_BIT, &dd->dd_flag) &&
	    !test_bit(MTIP_DDF_SEC_LOCK_BIT, &dd->dd_flag)) {
		rv = mtip_standby_immediate(dd->port);
		if (rv)
			dev_warn(&dd->pdev->dev,
				"STANDBY IMMEDIATE failed\n");
	}
	return rv;
}