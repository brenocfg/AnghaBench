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
typedef  int /*<<< orphan*/  u32 ;
struct r592_device {int /*<<< orphan*/  pio_fifo; } ;

/* Variables and functions */
 int /*<<< orphan*/  R592_FIFO_PIO ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  kfifo_in (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  kfifo_is_empty (int /*<<< orphan*/ *) ; 
 int kfifo_out (int /*<<< orphan*/ *,unsigned char*,int) ; 
 int min (int,int) ; 
 int /*<<< orphan*/  r592_read_reg_raw_be (struct r592_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void r592_read_fifo_pio(struct r592_device *dev,
						unsigned char *buffer, int len)
{
	u8 tmp[4];

	/* Read from last spill */
	if (!kfifo_is_empty(&dev->pio_fifo)) {
		int bytes_copied =
			kfifo_out(&dev->pio_fifo, buffer, min(4, len));
		buffer += bytes_copied;
		len -= bytes_copied;

		if (!kfifo_is_empty(&dev->pio_fifo))
			return;
	}

	/* Reads dwords from FIFO */
	while (len >= 4) {
		*(u32 *)buffer = r592_read_reg_raw_be(dev, R592_FIFO_PIO);
		buffer += 4;
		len -= 4;
	}

	if (len) {
		*(u32 *)tmp = r592_read_reg_raw_be(dev, R592_FIFO_PIO);
		kfifo_in(&dev->pio_fifo, tmp, 4);
		len -= kfifo_out(&dev->pio_fifo, buffer, len);
	}

	WARN_ON(len);
	return;
}