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
typedef  size_t u32 ;
typedef  int /*<<< orphan*/  t ;
struct wl1251 {size_t buffer_cmd; int /*<<< orphan*/ * buffer_busyword; } ;
struct spi_transfer {size_t* tx_buf; int len; int /*<<< orphan*/ * rx_buf; } ;
struct spi_message {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUG_SPI ; 
 int WL1251_BUSY_WORD_LEN ; 
 int WSPI_CMD_BYTE_ADDR ; 
 size_t WSPI_CMD_BYTE_LENGTH ; 
 size_t WSPI_CMD_BYTE_LENGTH_OFFSET ; 
 size_t WSPI_CMD_READ ; 
 int /*<<< orphan*/  memset (struct spi_transfer*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  spi_message_add_tail (struct spi_transfer*,struct spi_message*) ; 
 int /*<<< orphan*/  spi_message_init (struct spi_message*) ; 
 int /*<<< orphan*/  spi_sync (int /*<<< orphan*/ ,struct spi_message*) ; 
 int /*<<< orphan*/  wl1251_dump (int /*<<< orphan*/ ,char*,void*,size_t) ; 
 int /*<<< orphan*/  wl_to_spi (struct wl1251*) ; 

__attribute__((used)) static void wl1251_spi_read(struct wl1251 *wl, int addr, void *buf,
			    size_t len)
{
	struct spi_transfer t[3];
	struct spi_message m;
	u8 *busy_buf;
	u32 *cmd;

	cmd = &wl->buffer_cmd;
	busy_buf = wl->buffer_busyword;

	*cmd = 0;
	*cmd |= WSPI_CMD_READ;
	*cmd |= (len << WSPI_CMD_BYTE_LENGTH_OFFSET) & WSPI_CMD_BYTE_LENGTH;
	*cmd |= addr & WSPI_CMD_BYTE_ADDR;

	spi_message_init(&m);
	memset(t, 0, sizeof(t));

	t[0].tx_buf = cmd;
	t[0].len = 4;
	spi_message_add_tail(&t[0], &m);

	/* Busy and non busy words read */
	t[1].rx_buf = busy_buf;
	t[1].len = WL1251_BUSY_WORD_LEN;
	spi_message_add_tail(&t[1], &m);

	t[2].rx_buf = buf;
	t[2].len = len;
	spi_message_add_tail(&t[2], &m);

	spi_sync(wl_to_spi(wl), &m);

	/* FIXME: check busy words */

	wl1251_dump(DEBUG_SPI, "spi_read cmd -> ", cmd, sizeof(*cmd));
	wl1251_dump(DEBUG_SPI, "spi_read buf <- ", buf, len);
}