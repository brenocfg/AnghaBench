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
typedef  int /*<<< orphan*/  u16 ;
struct highlander_i2c_dev {int buf_len; int /*<<< orphan*/  dev; scalar_t__ base; int /*<<< orphan*/  buf; } ;

/* Variables and functions */
 int EAGAIN ; 
 scalar_t__ SMTRDR ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  highlander_i2c_start (struct highlander_i2c_dev*) ; 
 scalar_t__ highlander_i2c_wait_for_bbsy (struct highlander_i2c_dev*) ; 
 int highlander_i2c_wait_xfer_done (struct highlander_i2c_dev*) ; 
 int /*<<< orphan*/  iowrite16 (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  smbus_write_data (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int highlander_i2c_write(struct highlander_i2c_dev *dev)
{
	int i, cnt;
	u16 data[16];

	smbus_write_data(dev->buf, data, dev->buf_len);

	cnt = (dev->buf_len + 1) >> 1;
	for (i = 0; i < cnt; i++) {
		iowrite16(data[i], dev->base + SMTRDR + (i * sizeof(u16)));
		dev_dbg(dev->dev, "write data[%x] 0x%04x\n", i, data[i]);
	}

	if (highlander_i2c_wait_for_bbsy(dev))
		return -EAGAIN;

	highlander_i2c_start(dev);

	return highlander_i2c_wait_xfer_done(dev);
}