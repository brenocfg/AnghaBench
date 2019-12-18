#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u16 ;
typedef  int /*<<< orphan*/  t ;
struct spi_transfer {int* tx_buf; int len; int bits_per_word; } ;
struct spi_message {int dummy; } ;
struct eeprom_93xx46_platform_data {int /*<<< orphan*/  (* finish ) (struct eeprom_93xx46_dev*) ;int /*<<< orphan*/  (* prepare ) (struct eeprom_93xx46_dev*) ;} ;
struct eeprom_93xx46_dev {int addrlen; int /*<<< orphan*/  lock; TYPE_1__* spi; struct eeprom_93xx46_platform_data* pdata; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ADDR_ERAL ; 
 int OP_START ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int,int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 scalar_t__ has_quirk_instruction_length (struct eeprom_93xx46_dev*) ; 
 int /*<<< orphan*/  mdelay (int) ; 
 int /*<<< orphan*/  memset (struct spi_transfer*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spi_message_add_tail (struct spi_transfer*,struct spi_message*) ; 
 int /*<<< orphan*/  spi_message_init (struct spi_message*) ; 
 int spi_sync (TYPE_1__*,struct spi_message*) ; 
 int /*<<< orphan*/  stub1 (struct eeprom_93xx46_dev*) ; 
 int /*<<< orphan*/  stub2 (struct eeprom_93xx46_dev*) ; 

__attribute__((used)) static int eeprom_93xx46_eral(struct eeprom_93xx46_dev *edev)
{
	struct eeprom_93xx46_platform_data *pd = edev->pdata;
	struct spi_message m;
	struct spi_transfer t;
	int bits, ret;
	u16 cmd_addr;

	cmd_addr = OP_START << edev->addrlen;
	if (edev->addrlen == 7) {
		cmd_addr |= ADDR_ERAL << 1;
		bits = 10;
	} else {
		cmd_addr |= ADDR_ERAL;
		bits = 9;
	}

	if (has_quirk_instruction_length(edev)) {
		cmd_addr <<= 2;
		bits += 2;
	}

	dev_dbg(&edev->spi->dev, "eral cmd 0x%04x, %d bits\n", cmd_addr, bits);

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
	if (ret)
		dev_err(&edev->spi->dev, "erase error %d\n", ret);
	/* have to wait erase cycle time Tec ms */
	mdelay(6);

	if (pd->finish)
		pd->finish(edev);

	mutex_unlock(&edev->lock);
	return ret;
}