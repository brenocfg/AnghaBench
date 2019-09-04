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
 scalar_t__ kfifo_is_empty (int /*<<< orphan*/ *) ; 
 int kfifo_out (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  r592_write_reg_raw_be (struct r592_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void r592_flush_fifo_write(struct r592_device *dev)
{
	u8 buffer[4] = { 0 };
	int len;

	if (kfifo_is_empty(&dev->pio_fifo))
		return;

	len = kfifo_out(&dev->pio_fifo, buffer, 4);
	r592_write_reg_raw_be(dev, R592_FIFO_PIO, *(u32 *)buffer);
}