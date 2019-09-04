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
typedef  unsigned int u16 ;
struct spi_transfer {char* tx_buf; int len; int bits_per_word; char* rx_buf; int /*<<< orphan*/  member_0; } ;
struct spi_message {int dummy; } ;
struct eeprom_93xx46_dev {unsigned int size; unsigned int addrlen; int /*<<< orphan*/  lock; TYPE_1__* pdata; TYPE_2__* spi; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; int /*<<< orphan*/  max_speed_hz; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* finish ) (struct eeprom_93xx46_dev*) ;int /*<<< orphan*/  (* prepare ) (struct eeprom_93xx46_dev*) ;} ;

/* Variables and functions */
 unsigned int OP_READ ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,size_t,int,int) ; 
 scalar_t__ has_quirk_single_word_read (struct eeprom_93xx46_dev*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ndelay (int) ; 
 int /*<<< orphan*/  spi_message_add_tail (struct spi_transfer*,struct spi_message*) ; 
 int /*<<< orphan*/  spi_message_init (struct spi_message*) ; 
 int spi_sync (TYPE_2__*,struct spi_message*) ; 
 int /*<<< orphan*/  stub1 (struct eeprom_93xx46_dev*) ; 
 int /*<<< orphan*/  stub2 (struct eeprom_93xx46_dev*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int eeprom_93xx46_read(void *priv, unsigned int off,
			      void *val, size_t count)
{
	struct eeprom_93xx46_dev *edev = priv;
	char *buf = val;
	int err = 0;

	if (unlikely(off >= edev->size))
		return 0;
	if ((off + count) > edev->size)
		count = edev->size - off;
	if (unlikely(!count))
		return count;

	mutex_lock(&edev->lock);

	if (edev->pdata->prepare)
		edev->pdata->prepare(edev);

	while (count) {
		struct spi_message m;
		struct spi_transfer t[2] = { { 0 } };
		u16 cmd_addr = OP_READ << edev->addrlen;
		size_t nbytes = count;
		int bits;

		if (edev->addrlen == 7) {
			cmd_addr |= off & 0x7f;
			bits = 10;
			if (has_quirk_single_word_read(edev))
				nbytes = 1;
		} else {
			cmd_addr |= (off >> 1) & 0x3f;
			bits = 9;
			if (has_quirk_single_word_read(edev))
				nbytes = 2;
		}

		dev_dbg(&edev->spi->dev, "read cmd 0x%x, %d Hz\n",
			cmd_addr, edev->spi->max_speed_hz);

		spi_message_init(&m);

		t[0].tx_buf = (char *)&cmd_addr;
		t[0].len = 2;
		t[0].bits_per_word = bits;
		spi_message_add_tail(&t[0], &m);

		t[1].rx_buf = buf;
		t[1].len = count;
		t[1].bits_per_word = 8;
		spi_message_add_tail(&t[1], &m);

		err = spi_sync(edev->spi, &m);
		/* have to wait at least Tcsl ns */
		ndelay(250);

		if (err) {
			dev_err(&edev->spi->dev, "read %zu bytes at %d: err. %d\n",
				nbytes, (int)off, err);
			break;
		}

		buf += nbytes;
		off += nbytes;
		count -= nbytes;
	}

	if (edev->pdata->finish)
		edev->pdata->finish(edev);

	mutex_unlock(&edev->lock);

	return err;
}