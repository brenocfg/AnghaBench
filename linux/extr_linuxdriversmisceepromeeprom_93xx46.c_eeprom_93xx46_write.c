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
struct eeprom_93xx46_dev {unsigned int size; int addrlen; int /*<<< orphan*/  lock; TYPE_2__* pdata; TYPE_1__* spi; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* finish ) (struct eeprom_93xx46_dev*) ;int /*<<< orphan*/  (* prepare ) (struct eeprom_93xx46_dev*) ;} ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EFBIG ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int,int) ; 
 int eeprom_93xx46_ew (struct eeprom_93xx46_dev*,int) ; 
 int eeprom_93xx46_write_word (struct eeprom_93xx46_dev*,char*,unsigned int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct eeprom_93xx46_dev*) ; 
 int /*<<< orphan*/  stub2 (struct eeprom_93xx46_dev*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int eeprom_93xx46_write(void *priv, unsigned int off,
				   void *val, size_t count)
{
	struct eeprom_93xx46_dev *edev = priv;
	char *buf = val;
	int i, ret, step = 1;

	if (unlikely(off >= edev->size))
		return -EFBIG;
	if ((off + count) > edev->size)
		count = edev->size - off;
	if (unlikely(!count))
		return count;

	/* only write even number of bytes on 16-bit devices */
	if (edev->addrlen == 6) {
		step = 2;
		count &= ~1;
	}

	/* erase/write enable */
	ret = eeprom_93xx46_ew(edev, 1);
	if (ret)
		return ret;

	mutex_lock(&edev->lock);

	if (edev->pdata->prepare)
		edev->pdata->prepare(edev);

	for (i = 0; i < count; i += step) {
		ret = eeprom_93xx46_write_word(edev, &buf[i], off + i);
		if (ret) {
			dev_err(&edev->spi->dev, "write failed at %d: %d\n",
				(int)off + i, ret);
			break;
		}
	}

	if (edev->pdata->finish)
		edev->pdata->finish(edev);

	mutex_unlock(&edev->lock);

	/* erase/write disable */
	eeprom_93xx46_ew(edev, 0);
	return ret;
}