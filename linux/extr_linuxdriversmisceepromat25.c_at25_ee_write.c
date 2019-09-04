#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_4__ {unsigned int byte_len; unsigned int page_size; int flags; } ;
struct at25_data {unsigned int addrlen; int /*<<< orphan*/  lock; TYPE_2__* spi; TYPE_1__ chip; } ;
struct TYPE_5__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  AT25_INSTR_BIT3 ; 
 int /*<<< orphan*/  AT25_RDSR ; 
 int AT25_SR_nRDY ; 
 int /*<<< orphan*/  AT25_WREN ; 
 int /*<<< orphan*/  AT25_WRITE ; 
 int EE_INSTR_BIT3_IS_ADDR ; 
 unsigned long EE_TIMEOUT ; 
 int EFBIG ; 
 int EINVAL ; 
 int ENOMEM ; 
 int ETIMEDOUT ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int,...) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,unsigned int,unsigned int,int /*<<< orphan*/ ) ; 
 unsigned int io_limit ; 
 unsigned long jiffies ; 
 int /*<<< orphan*/  jiffies_to_msecs (unsigned long) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * kmalloc (unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,char const*,unsigned int) ; 
 unsigned long msecs_to_jiffies (unsigned long) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int spi_w8r8 (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int spi_write (TYPE_2__*,int /*<<< orphan*/ *,unsigned int) ; 
 scalar_t__ time_before_eq (unsigned long,unsigned long) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int at25_ee_write(void *priv, unsigned int off, void *val, size_t count)
{
	struct at25_data *at25 = priv;
	const char *buf = val;
	int			status = 0;
	unsigned		buf_size;
	u8			*bounce;

	if (unlikely(off >= at25->chip.byte_len))
		return -EFBIG;
	if ((off + count) > at25->chip.byte_len)
		count = at25->chip.byte_len - off;
	if (unlikely(!count))
		return -EINVAL;

	/* Temp buffer starts with command and address */
	buf_size = at25->chip.page_size;
	if (buf_size > io_limit)
		buf_size = io_limit;
	bounce = kmalloc(buf_size + at25->addrlen + 1, GFP_KERNEL);
	if (!bounce)
		return -ENOMEM;

	/* For write, rollover is within the page ... so we write at
	 * most one page, then manually roll over to the next page.
	 */
	mutex_lock(&at25->lock);
	do {
		unsigned long	timeout, retries;
		unsigned	segment;
		unsigned	offset = (unsigned) off;
		u8		*cp = bounce;
		int		sr;
		u8		instr;

		*cp = AT25_WREN;
		status = spi_write(at25->spi, cp, 1);
		if (status < 0) {
			dev_dbg(&at25->spi->dev, "WREN --> %d\n", status);
			break;
		}

		instr = AT25_WRITE;
		if (at25->chip.flags & EE_INSTR_BIT3_IS_ADDR)
			if (offset >= (1U << (at25->addrlen * 8)))
				instr |= AT25_INSTR_BIT3;
		*cp++ = instr;

		/* 8/16/24-bit address is written MSB first */
		switch (at25->addrlen) {
		default:	/* case 3 */
			*cp++ = offset >> 16;
			/* fall through */
		case 2:
			*cp++ = offset >> 8;
			/* fall through */
		case 1:
		case 0:	/* can't happen: for better codegen */
			*cp++ = offset >> 0;
		}

		/* Write as much of a page as we can */
		segment = buf_size - (offset % buf_size);
		if (segment > count)
			segment = count;
		memcpy(cp, buf, segment);
		status = spi_write(at25->spi, bounce,
				segment + at25->addrlen + 1);
		dev_dbg(&at25->spi->dev, "write %u bytes at %u --> %d\n",
			segment, offset, status);
		if (status < 0)
			break;

		/* REVISIT this should detect (or prevent) failed writes
		 * to readonly sections of the EEPROM...
		 */

		/* Wait for non-busy status */
		timeout = jiffies + msecs_to_jiffies(EE_TIMEOUT);
		retries = 0;
		do {

			sr = spi_w8r8(at25->spi, AT25_RDSR);
			if (sr < 0 || (sr & AT25_SR_nRDY)) {
				dev_dbg(&at25->spi->dev,
					"rdsr --> %d (%02x)\n", sr, sr);
				/* at HZ=100, this is sloooow */
				msleep(1);
				continue;
			}
			if (!(sr & AT25_SR_nRDY))
				break;
		} while (retries++ < 3 || time_before_eq(jiffies, timeout));

		if ((sr < 0) || (sr & AT25_SR_nRDY)) {
			dev_err(&at25->spi->dev,
				"write %u bytes offset %u, timeout after %u msecs\n",
				segment, offset,
				jiffies_to_msecs(jiffies -
					(timeout - EE_TIMEOUT)));
			status = -ETIMEDOUT;
			break;
		}

		off += segment;
		buf += segment;
		count -= segment;

	} while (count > 0);

	mutex_unlock(&at25->lock);

	kfree(bounce);
	return status;
}