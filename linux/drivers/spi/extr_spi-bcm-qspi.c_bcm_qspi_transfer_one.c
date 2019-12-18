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
struct spi_transfer {scalar_t__ len; } ;
struct spi_master {int dummy; } ;
struct spi_device {int /*<<< orphan*/  chip_select; } ;
struct TYPE_3__ {scalar_t__ byte; struct spi_transfer* trans; } ;
struct bcm_qspi {TYPE_2__* pdev; int /*<<< orphan*/  mspi_done; TYPE_1__ trans_pos; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ETIMEDOUT ; 
 int /*<<< orphan*/  bcm_qspi_chip_select (struct bcm_qspi*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bcm_qspi_enable_bspi (struct bcm_qspi*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 unsigned long msecs_to_jiffies (int) ; 
 int /*<<< orphan*/  read_from_hw (struct bcm_qspi*,int) ; 
 int /*<<< orphan*/  reinit_completion (int /*<<< orphan*/ *) ; 
 struct bcm_qspi* spi_master_get_devdata (struct spi_master*) ; 
 int /*<<< orphan*/  wait_for_completion_timeout (int /*<<< orphan*/ *,unsigned long) ; 
 int write_to_hw (struct bcm_qspi*,struct spi_device*) ; 

__attribute__((used)) static int bcm_qspi_transfer_one(struct spi_master *master,
				 struct spi_device *spi,
				 struct spi_transfer *trans)
{
	struct bcm_qspi *qspi = spi_master_get_devdata(master);
	int slots;
	unsigned long timeo = msecs_to_jiffies(100);

	bcm_qspi_chip_select(qspi, spi->chip_select);
	qspi->trans_pos.trans = trans;
	qspi->trans_pos.byte = 0;

	while (qspi->trans_pos.byte < trans->len) {
		reinit_completion(&qspi->mspi_done);

		slots = write_to_hw(qspi, spi);
		if (!wait_for_completion_timeout(&qspi->mspi_done, timeo)) {
			dev_err(&qspi->pdev->dev, "timeout waiting for MSPI\n");
			return -ETIMEDOUT;
		}

		read_from_hw(qspi, slots);
	}
	bcm_qspi_enable_bspi(qspi);

	return 0;
}