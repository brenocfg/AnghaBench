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
struct TYPE_2__ {scalar_t__ count; int /*<<< orphan*/  xfer_bytes; int /*<<< orphan*/ * buffer; } ;
struct nmk_i2c_dev {TYPE_1__ cli; scalar_t__ virtbase; } ;

/* Variables and functions */
 scalar_t__ I2C_TFR ; 
 int /*<<< orphan*/  writeb (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void fill_tx_fifo(struct nmk_i2c_dev *dev, int no_bytes)
{
	int count;

	for (count = (no_bytes - 2);
			(count > 0) &&
			(dev->cli.count != 0);
			count--) {
		/* write to the Tx FIFO */
		writeb(*dev->cli.buffer,
			dev->virtbase + I2C_TFR);
		dev->cli.buffer++;
		dev->cli.count--;
		dev->cli.xfer_bytes++;
	}

}