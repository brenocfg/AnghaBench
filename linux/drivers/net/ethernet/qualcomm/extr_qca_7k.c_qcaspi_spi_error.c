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
struct TYPE_2__ {int /*<<< orphan*/  spi_err; } ;
struct qcaspi {scalar_t__ sync; TYPE_1__ stats; int /*<<< orphan*/  net_dev; } ;

/* Variables and functions */
 scalar_t__ QCASPI_SYNC_READY ; 
 scalar_t__ QCASPI_SYNC_UNKNOWN ; 
 int /*<<< orphan*/  netdev_err (int /*<<< orphan*/ ,char*) ; 

void
qcaspi_spi_error(struct qcaspi *qca)
{
	if (qca->sync != QCASPI_SYNC_READY)
		return;

	netdev_err(qca->net_dev, "spi error\n");
	qca->sync = QCASPI_SYNC_UNKNOWN;
	qca->stats.spi_err++;
}