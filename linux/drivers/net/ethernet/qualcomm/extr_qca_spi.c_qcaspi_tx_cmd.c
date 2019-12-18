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
typedef  int /*<<< orphan*/  u16 ;
typedef  int /*<<< orphan*/  transfer ;
struct spi_transfer {int len; int /*<<< orphan*/ * tx_buf; } ;
struct spi_message {int status; } ;
struct qcaspi {int /*<<< orphan*/  spi_dev; } ;
typedef  int /*<<< orphan*/  cmd ;
typedef  int /*<<< orphan*/  __be16 ;

/* Variables and functions */
 int /*<<< orphan*/  cpu_to_be16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct spi_transfer*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  qcaspi_spi_error (struct qcaspi*) ; 
 int /*<<< orphan*/  spi_message_add_tail (struct spi_transfer*,struct spi_message*) ; 
 int /*<<< orphan*/  spi_message_init (struct spi_message*) ; 
 int spi_sync (int /*<<< orphan*/ ,struct spi_message*) ; 

__attribute__((used)) static int
qcaspi_tx_cmd(struct qcaspi *qca, u16 cmd)
{
	__be16 tx_data;
	struct spi_message msg;
	struct spi_transfer transfer;
	int ret;

	memset(&transfer, 0, sizeof(transfer));

	spi_message_init(&msg);

	tx_data = cpu_to_be16(cmd);
	transfer.len = sizeof(cmd);
	transfer.tx_buf = &tx_data;
	spi_message_add_tail(&transfer, &msg);

	ret = spi_sync(qca->spi_dev, &msg);

	if (!ret)
		ret = msg.status;

	if (ret)
		qcaspi_spi_error(qca);

	return ret;
}