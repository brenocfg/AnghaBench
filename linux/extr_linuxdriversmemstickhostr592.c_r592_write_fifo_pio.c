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
 int kfifo_in (int /*<<< orphan*/ *,unsigned char*,int) ; 
 int /*<<< orphan*/  kfifo_is_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfifo_is_full (int /*<<< orphan*/ *) ; 
 int kfifo_out (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  r592_write_reg_raw_be (struct r592_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void r592_write_fifo_pio(struct r592_device *dev,
					unsigned char *buffer, int len)
{
	/* flush spill from former write */
	if (!kfifo_is_empty(&dev->pio_fifo)) {

		u8 tmp[4] = {0};
		int copy_len = kfifo_in(&dev->pio_fifo, buffer, len);

		if (!kfifo_is_full(&dev->pio_fifo))
			return;
		len -= copy_len;
		buffer += copy_len;

		copy_len = kfifo_out(&dev->pio_fifo, tmp, 4);
		WARN_ON(copy_len != 4);
		r592_write_reg_raw_be(dev, R592_FIFO_PIO, *(u32 *)tmp);
	}

	WARN_ON(!kfifo_is_empty(&dev->pio_fifo));

	/* write full dwords */
	while (len >= 4) {
		r592_write_reg_raw_be(dev, R592_FIFO_PIO, *(u32 *)buffer);
		buffer += 4;
		len -= 4;
	}

	/* put remaining bytes to the spill */
	if (len)
		kfifo_in(&dev->pio_fifo, buffer, len);
}