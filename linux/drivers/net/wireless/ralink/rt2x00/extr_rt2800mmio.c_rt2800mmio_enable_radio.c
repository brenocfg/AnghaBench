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
struct rt2x00_dev {int dummy; } ;

/* Variables and functions */
 int EIO ; 
 int rt2800_enable_radio (struct rt2x00_dev*) ; 
 int /*<<< orphan*/  rt2800_wait_wpdma_ready (struct rt2x00_dev*) ; 
 int /*<<< orphan*/  rt2800mmio_init_queues (struct rt2x00_dev*) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

int rt2800mmio_enable_radio(struct rt2x00_dev *rt2x00dev)
{
	/* Wait for DMA, ignore error until we initialize queues. */
	rt2800_wait_wpdma_ready(rt2x00dev);

	if (unlikely(rt2800mmio_init_queues(rt2x00dev)))
		return -EIO;

	return rt2800_enable_radio(rt2x00dev);
}