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
typedef  int /*<<< orphan*/  u8 ;
typedef  scalar_t__ u32 ;
typedef  int /*<<< orphan*/  transfer ;
struct spi_transfer {scalar_t__ len; int /*<<< orphan*/ * rx_buf; } ;
struct spi_message {scalar_t__ actual_length; } ;
struct qcaspi {int /*<<< orphan*/  spi_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  memset (struct spi_transfer*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  qcaspi_spi_error (struct qcaspi*) ; 
 int /*<<< orphan*/  spi_message_add_tail (struct spi_transfer*,struct spi_message*) ; 
 int /*<<< orphan*/  spi_message_init (struct spi_message*) ; 
 int spi_sync (int /*<<< orphan*/ ,struct spi_message*) ; 

__attribute__((used)) static u32
qcaspi_read_legacy(struct qcaspi *qca, u8 *dst, u32 len)
{
	struct spi_message msg;
	struct spi_transfer transfer;
	int ret;

	memset(&transfer, 0, sizeof(transfer));
	spi_message_init(&msg);

	transfer.rx_buf = dst;
	transfer.len = len;

	spi_message_add_tail(&transfer, &msg);
	ret = spi_sync(qca->spi_dev, &msg);

	if (ret || (msg.actual_length != len)) {
		qcaspi_spi_error(qca);
		return 0;
	}

	return len;
}