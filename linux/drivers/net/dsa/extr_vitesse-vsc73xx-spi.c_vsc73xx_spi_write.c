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
typedef  int u32 ;
typedef  int /*<<< orphan*/  t ;
struct vsc73xx_spi {int /*<<< orphan*/  lock; int /*<<< orphan*/  spi; } ;
struct vsc73xx {struct vsc73xx_spi* priv; } ;
struct spi_transfer {int* tx_buf; int len; } ;
struct spi_message {int dummy; } ;
typedef  int /*<<< orphan*/  cmd ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  VSC73XX_CMD_SPI_MODE_WRITE ; 
 int /*<<< orphan*/  memset (struct spi_transfer**,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spi_message_add_tail (struct spi_transfer*,struct spi_message*) ; 
 int /*<<< orphan*/  spi_message_init (struct spi_message*) ; 
 int spi_sync (int /*<<< orphan*/ ,struct spi_message*) ; 
 int /*<<< orphan*/  vsc73xx_is_addr_valid (int,int) ; 
 int vsc73xx_make_addr (int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static int vsc73xx_spi_write(struct vsc73xx *vsc, u8 block, u8 subblock, u8 reg,
			     u32 val)
{
	struct vsc73xx_spi *vsc_spi = vsc->priv;
	struct spi_transfer t[2];
	struct spi_message m;
	u8 cmd[2];
	u8 buf[4];
	int ret;

	if (!vsc73xx_is_addr_valid(block, subblock))
		return -EINVAL;

	spi_message_init(&m);

	memset(&t, 0, sizeof(t));

	t[0].tx_buf = cmd;
	t[0].len = sizeof(cmd);
	spi_message_add_tail(&t[0], &m);

	t[1].tx_buf = buf;
	t[1].len = sizeof(buf);
	spi_message_add_tail(&t[1], &m);

	cmd[0] = vsc73xx_make_addr(VSC73XX_CMD_SPI_MODE_WRITE, block, subblock);
	cmd[1] = reg;

	buf[0] = (val >> 24) & 0xff;
	buf[1] = (val >> 16) & 0xff;
	buf[2] = (val >> 8) & 0xff;
	buf[3] = val & 0xff;

	mutex_lock(&vsc_spi->lock);
	ret = spi_sync(vsc_spi->spi, &m);
	mutex_unlock(&vsc_spi->lock);

	return ret;
}