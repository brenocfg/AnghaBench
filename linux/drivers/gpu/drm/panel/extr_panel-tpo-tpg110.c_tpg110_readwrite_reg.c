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
typedef  int u8 ;
typedef  int /*<<< orphan*/  t ;
struct tpg110 {int /*<<< orphan*/  dev; int /*<<< orphan*/  spi; } ;
struct spi_transfer {int bits_per_word; int* tx_buf; int len; int* rx_buf; } ;
struct spi_message {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEV_ERROR (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  memset (struct spi_transfer*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  spi_message_add_tail (struct spi_transfer*,struct spi_message*) ; 
 int /*<<< orphan*/  spi_message_init (struct spi_message*) ; 
 int spi_sync (int /*<<< orphan*/ ,struct spi_message*) ; 

__attribute__((used)) static u8 tpg110_readwrite_reg(struct tpg110 *tpg, bool write,
			       u8 address, u8 outval)
{
	struct spi_message m;
	struct spi_transfer t[2];
	u8 buf[2];
	int ret;

	spi_message_init(&m);
	memset(t, 0, sizeof(t));

	if (write) {
		/*
		 * Clear address bit 0, 1 when writing, just to be sure
		 * The actual bit indicating a write here is bit 1, bit
		 * 0 is just surplus to pad it up to 8 bits.
		 */
		buf[0] = address << 2;
		buf[0] &= ~0x03;
		buf[1] = outval;

		t[0].bits_per_word = 8;
		t[0].tx_buf = &buf[0];
		t[0].len = 1;

		t[1].tx_buf = &buf[1];
		t[1].len = 1;
		t[1].bits_per_word = 8;
	} else {
		/* Set address bit 0 to 1 to read */
		buf[0] = address << 1;
		buf[0] |= 0x01;

		/*
		 * The last bit/clock is Hi-Z turnaround cycle, so we need
		 * to send only 7 bits here. The 8th bit is the high impedance
		 * turn-around cycle.
		 */
		t[0].bits_per_word = 7;
		t[0].tx_buf = &buf[0];
		t[0].len = 1;

		t[1].rx_buf = &buf[1];
		t[1].len = 1;
		t[1].bits_per_word = 8;
	}

	spi_message_add_tail(&t[0], &m);
	spi_message_add_tail(&t[1], &m);
	ret = spi_sync(tpg->spi, &m);
	if (ret) {
		DRM_DEV_ERROR(tpg->dev, "SPI message error %d\n", ret);
		return ret;
	}
	if (write)
		return 0;
	/* Read */
	return buf[1];
}