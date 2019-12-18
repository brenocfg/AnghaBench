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
struct spi_device {int dummy; } ;
struct lm70 {int chip; int /*<<< orphan*/  lock; struct spi_device* spi; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int ssize_t ;
typedef  int s16 ;

/* Variables and functions */
 int ERESTARTSYS ; 
#define  LM70_CHIP_LM70 132 
#define  LM70_CHIP_LM71 131 
#define  LM70_CHIP_LM74 130 
#define  LM70_CHIP_TMP121 129 
#define  LM70_CHIP_TMP122 128 
 int /*<<< orphan*/  dev_dbg (struct device*,char*,int,int,int) ; 
 struct lm70* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  dev_warn (struct device*,char*,int) ; 
 scalar_t__ mutex_lock_interruptible (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int spi_write_then_read (struct spi_device*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int*,int) ; 
 int sprintf (char*,char*,int) ; 

__attribute__((used)) static ssize_t temp1_input_show(struct device *dev,
				struct device_attribute *attr, char *buf)
{
	struct lm70 *p_lm70 = dev_get_drvdata(dev);
	struct spi_device *spi = p_lm70->spi;
	int status, val = 0;
	u8 rxbuf[2];
	s16 raw = 0;

	if (mutex_lock_interruptible(&p_lm70->lock))
		return -ERESTARTSYS;

	/*
	 * spi_read() requires a DMA-safe buffer; so we use
	 * spi_write_then_read(), transmitting 0 bytes.
	 */
	status = spi_write_then_read(spi, NULL, 0, &rxbuf[0], 2);
	if (status < 0) {
		dev_warn(dev, "spi_write_then_read failed with status %d\n",
			 status);
		goto out;
	}
	raw = (rxbuf[0] << 8) + rxbuf[1];
	dev_dbg(dev, "rxbuf[0] : 0x%02x rxbuf[1] : 0x%02x raw=0x%04x\n",
		rxbuf[0], rxbuf[1], raw);

	/*
	 * LM70:
	 * The "raw" temperature read into rxbuf[] is a 16-bit signed 2's
	 * complement value. Only the MSB 11 bits (1 sign + 10 temperature
	 * bits) are meaningful; the LSB 5 bits are to be discarded.
	 * See the datasheet.
	 *
	 * Further, each bit represents 0.25 degrees Celsius; so, multiply
	 * by 0.25. Also multiply by 1000 to represent in millidegrees
	 * Celsius.
	 * So it's equivalent to multiplying by 0.25 * 1000 = 250.
	 *
	 * LM74 and TMP121/TMP122/TMP123/TMP124:
	 * 13 bits of 2's complement data, discard LSB 3 bits,
	 * resolution 0.0625 degrees celsius.
	 *
	 * LM71:
	 * 14 bits of 2's complement data, discard LSB 2 bits,
	 * resolution 0.0312 degrees celsius.
	 */
	switch (p_lm70->chip) {
	case LM70_CHIP_LM70:
		val = ((int)raw / 32) * 250;
		break;

	case LM70_CHIP_TMP121:
	case LM70_CHIP_TMP122:
	case LM70_CHIP_LM74:
		val = ((int)raw / 8) * 625 / 10;
		break;

	case LM70_CHIP_LM71:
		val = ((int)raw / 4) * 3125 / 100;
		break;
	}

	status = sprintf(buf, "%d\n", val); /* millidegrees Celsius */
out:
	mutex_unlock(&p_lm70->lock);
	return status;
}