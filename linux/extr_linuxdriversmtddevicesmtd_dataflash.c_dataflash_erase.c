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
struct spi_transfer {int len; int /*<<< orphan*/ * tx_buf; } ;
struct spi_message {int dummy; } ;
struct spi_device {int /*<<< orphan*/  dev; } ;
struct mtd_info {struct dataflash* priv; } ;
struct erase_info {scalar_t__ addr; scalar_t__ len; } ;
struct dataflash {int page_size; unsigned int page_offset; int /*<<< orphan*/  lock; int /*<<< orphan*/ * command; struct spi_device* spi; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  OP_ERASE_BLOCK ; 
 int /*<<< orphan*/  OP_ERASE_PAGE ; 
 int /*<<< orphan*/  dataflash_waitready (struct spi_device*) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,unsigned int,int) ; 
 unsigned int div_u64 (scalar_t__,int) ; 
 int /*<<< orphan*/  div_u64_rem (scalar_t__,int,scalar_t__*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spi_message_add_tail (struct spi_transfer*,struct spi_message*) ; 
 int /*<<< orphan*/  spi_message_init (struct spi_message*) ; 
 int spi_sync (struct spi_device*,struct spi_message*) ; 

__attribute__((used)) static int dataflash_erase(struct mtd_info *mtd, struct erase_info *instr)
{
	struct dataflash	*priv = mtd->priv;
	struct spi_device	*spi = priv->spi;
	struct spi_transfer	x = { };
	struct spi_message	msg;
	unsigned		blocksize = priv->page_size << 3;
	u8			*command;
	u32			rem;

	dev_dbg(&spi->dev, "erase addr=0x%llx len 0x%llx\n",
		(long long)instr->addr, (long long)instr->len);

	div_u64_rem(instr->len, priv->page_size, &rem);
	if (rem)
		return -EINVAL;
	div_u64_rem(instr->addr, priv->page_size, &rem);
	if (rem)
		return -EINVAL;

	spi_message_init(&msg);

	x.tx_buf = command = priv->command;
	x.len = 4;
	spi_message_add_tail(&x, &msg);

	mutex_lock(&priv->lock);
	while (instr->len > 0) {
		unsigned int	pageaddr;
		int		status;
		int		do_block;

		/* Calculate flash page address; use block erase (for speed) if
		 * we're at a block boundary and need to erase the whole block.
		 */
		pageaddr = div_u64(instr->addr, priv->page_size);
		do_block = (pageaddr & 0x7) == 0 && instr->len >= blocksize;
		pageaddr = pageaddr << priv->page_offset;

		command[0] = do_block ? OP_ERASE_BLOCK : OP_ERASE_PAGE;
		command[1] = (u8)(pageaddr >> 16);
		command[2] = (u8)(pageaddr >> 8);
		command[3] = 0;

		dev_dbg(&spi->dev, "ERASE %s: (%x) %x %x %x [%i]\n",
			do_block ? "block" : "page",
			command[0], command[1], command[2], command[3],
			pageaddr);

		status = spi_sync(spi, &msg);
		(void) dataflash_waitready(spi);

		if (status < 0) {
			dev_err(&spi->dev, "erase %x, err %d\n",
				pageaddr, status);
			/* REVISIT:  can retry instr->retries times; or
			 * giveup and instr->fail_addr = instr->addr;
			 */
			continue;
		}

		if (do_block) {
			instr->addr += blocksize;
			instr->len -= blocksize;
		} else {
			instr->addr += priv->page_size;
			instr->len -= priv->page_size;
		}
	}
	mutex_unlock(&priv->lock);

	return 0;
}