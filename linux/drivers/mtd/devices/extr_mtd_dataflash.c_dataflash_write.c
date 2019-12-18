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
typedef  unsigned int u_char ;
typedef  unsigned int u8 ;
struct spi_transfer {unsigned int* tx_buf; int len; } ;
struct spi_message {int dummy; } ;
struct spi_device {int /*<<< orphan*/  dev; } ;
struct mtd_info {struct dataflash* priv; } ;
struct dataflash {unsigned int* command; unsigned int page_size; unsigned int page_offset; int /*<<< orphan*/  lock; struct spi_device* spi; } ;
typedef  scalar_t__ loff_t ;

/* Variables and functions */
 int EINVAL ; 
 int EIO ; 
 unsigned int OP_COMPARE_BUF1 ; 
 unsigned int OP_PROGRAM_VIA_BUF1 ; 
 unsigned int OP_TRANSFER_BUF1 ; 
 int dataflash_waitready (struct spi_device*) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,unsigned int,int,...) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,unsigned int,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spi_message_add_tail (struct spi_transfer*,struct spi_message*) ; 
 int /*<<< orphan*/  spi_message_init (struct spi_message*) ; 
 int spi_sync (struct spi_device*,struct spi_message*) ; 
 int /*<<< orphan*/  spi_transfer_del (struct spi_transfer*) ; 

__attribute__((used)) static int dataflash_write(struct mtd_info *mtd, loff_t to, size_t len,
				size_t * retlen, const u_char * buf)
{
	struct dataflash	*priv = mtd->priv;
	struct spi_device	*spi = priv->spi;
	struct spi_transfer	x[2] = { };
	struct spi_message	msg;
	unsigned int		pageaddr, addr, offset, writelen;
	size_t			remaining = len;
	u_char			*writebuf = (u_char *) buf;
	int			status = -EINVAL;
	u8			*command;

	dev_dbg(&spi->dev, "write 0x%x..0x%x\n",
		(unsigned int)to, (unsigned int)(to + len));

	spi_message_init(&msg);

	x[0].tx_buf = command = priv->command;
	x[0].len = 4;
	spi_message_add_tail(&x[0], &msg);

	pageaddr = ((unsigned)to / priv->page_size);
	offset = ((unsigned)to % priv->page_size);
	if (offset + len > priv->page_size)
		writelen = priv->page_size - offset;
	else
		writelen = len;

	mutex_lock(&priv->lock);
	while (remaining > 0) {
		dev_dbg(&spi->dev, "write @ %i:%i len=%i\n",
			pageaddr, offset, writelen);

		/* REVISIT:
		 * (a) each page in a sector must be rewritten at least
		 *     once every 10K sibling erase/program operations.
		 * (b) for pages that are already erased, we could
		 *     use WRITE+MWRITE not PROGRAM for ~30% speedup.
		 * (c) WRITE to buffer could be done while waiting for
		 *     a previous MWRITE/MWERASE to complete ...
		 * (d) error handling here seems to be mostly missing.
		 *
		 * Two persistent bits per page, plus a per-sector counter,
		 * could support (a) and (b) ... we might consider using
		 * the second half of sector zero, which is just one block,
		 * to track that state.  (On AT91, that sector should also
		 * support boot-from-DataFlash.)
		 */

		addr = pageaddr << priv->page_offset;

		/* (1) Maybe transfer partial page to Buffer1 */
		if (writelen != priv->page_size) {
			command[0] = OP_TRANSFER_BUF1;
			command[1] = (addr & 0x00FF0000) >> 16;
			command[2] = (addr & 0x0000FF00) >> 8;
			command[3] = 0;

			dev_dbg(&spi->dev, "TRANSFER: (%x) %x %x %x\n",
				command[0], command[1], command[2], command[3]);

			status = spi_sync(spi, &msg);
			if (status < 0)
				dev_dbg(&spi->dev, "xfer %u -> %d\n",
					addr, status);

			(void) dataflash_waitready(priv->spi);
		}

		/* (2) Program full page via Buffer1 */
		addr += offset;
		command[0] = OP_PROGRAM_VIA_BUF1;
		command[1] = (addr & 0x00FF0000) >> 16;
		command[2] = (addr & 0x0000FF00) >> 8;
		command[3] = (addr & 0x000000FF);

		dev_dbg(&spi->dev, "PROGRAM: (%x) %x %x %x\n",
			command[0], command[1], command[2], command[3]);

		x[1].tx_buf = writebuf;
		x[1].len = writelen;
		spi_message_add_tail(x + 1, &msg);
		status = spi_sync(spi, &msg);
		spi_transfer_del(x + 1);
		if (status < 0)
			dev_dbg(&spi->dev, "pgm %u/%u -> %d\n",
				addr, writelen, status);

		(void) dataflash_waitready(priv->spi);


#ifdef CONFIG_MTD_DATAFLASH_WRITE_VERIFY

		/* (3) Compare to Buffer1 */
		addr = pageaddr << priv->page_offset;
		command[0] = OP_COMPARE_BUF1;
		command[1] = (addr & 0x00FF0000) >> 16;
		command[2] = (addr & 0x0000FF00) >> 8;
		command[3] = 0;

		dev_dbg(&spi->dev, "COMPARE: (%x) %x %x %x\n",
			command[0], command[1], command[2], command[3]);

		status = spi_sync(spi, &msg);
		if (status < 0)
			dev_dbg(&spi->dev, "compare %u -> %d\n",
				addr, status);

		status = dataflash_waitready(priv->spi);

		/* Check result of the compare operation */
		if (status & (1 << 6)) {
			dev_err(&spi->dev, "compare page %u, err %d\n",
				pageaddr, status);
			remaining = 0;
			status = -EIO;
			break;
		} else
			status = 0;

#endif	/* CONFIG_MTD_DATAFLASH_WRITE_VERIFY */

		remaining = remaining - writelen;
		pageaddr++;
		offset = 0;
		writebuf += writelen;
		*retlen += writelen;

		if (remaining > priv->page_size)
			writelen = priv->page_size;
		else
			writelen = remaining;
	}
	mutex_unlock(&priv->lock);

	return status;
}