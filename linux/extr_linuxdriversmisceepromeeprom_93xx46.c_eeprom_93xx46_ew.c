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
typedef  int u16 ;
typedef  int /*<<< orphan*/  t ;
struct spi_transfer {int* tx_buf; int len; int bits_per_word; } ;
struct spi_message {int dummy; } ;
struct eeprom_93xx46_dev {int addrlen; int /*<<< orphan*/  lock; TYPE_1__* pdata; TYPE_2__* spi; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* finish ) (struct eeprom_93xx46_dev*) ;int /*<<< orphan*/  (* prepare ) (struct eeprom_93xx46_dev*) ;} ;

/* Variables and functions */
 int ADDR_EWDS ; 
 int ADDR_EWEN ; 
 int OP_START ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,char*,int,int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,char*,int) ; 
 scalar_t__ has_quirk_instruction_length (struct eeprom_93xx46_dev*) ; 
 int /*<<< orphan*/  memset (struct spi_transfer*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ndelay (int) ; 
 int /*<<< orphan*/  spi_message_add_tail (struct spi_transfer*,struct spi_message*) ; 
 int /*<<< orphan*/  spi_message_init (struct spi_message*) ; 
 int spi_sync (TYPE_2__*,struct spi_message*) ; 
 int /*<<< orphan*/  stub1 (struct eeprom_93xx46_dev*) ; 
 int /*<<< orphan*/  stub2 (struct eeprom_93xx46_dev*) ; 

__attribute__((used)) static int eeprom_93xx46_ew(struct eeprom_93xx46_dev *edev, int is_on)
{
	struct spi_message m;
	struct spi_transfer t;
	int bits, ret;
	u16 cmd_addr;

	cmd_addr = OP_START << edev->addrlen;
	if (edev->addrlen == 7) {
		cmd_addr |= (is_on ? ADDR_EWEN : ADDR_EWDS) << 1;
		bits = 10;
	} else {
		cmd_addr |= (is_on ? ADDR_EWEN : ADDR_EWDS);
		bits = 9;
	}

	if (has_quirk_instruction_length(edev)) {
		cmd_addr <<= 2;
		bits += 2;
	}

	dev_dbg(&edev->spi->dev, "ew%s cmd 0x%04x, %d bits\n",
			is_on ? "en" : "ds", cmd_addr, bits);

	spi_message_init(&m);
	memset(&t, 0, sizeof(t));

	t.tx_buf = &cmd_addr;
	t.len = 2;
	t.bits_per_word = bits;
	spi_message_add_tail(&t, &m);

	mutex_lock(&edev->lock);

	if (edev->pdata->prepare)
		edev->pdata->prepare(edev);

	ret = spi_sync(edev->spi, &m);
	/* have to wait at least Tcsl ns */
	ndelay(250);
	if (ret)
		dev_err(&edev->spi->dev, "erase/write %sable error %d\n",
			is_on ? "en" : "dis", ret);

	if (edev->pdata->finish)
		edev->pdata->finish(edev);

	mutex_unlock(&edev->lock);
	return ret;
}