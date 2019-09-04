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
struct sg_mapping_iter {int /*<<< orphan*/  length; int /*<<< orphan*/  addr; } ;
struct r592_device {TYPE_1__* req; int /*<<< orphan*/  pio_fifo; } ;
struct TYPE_2__ {scalar_t__ tpc; int /*<<< orphan*/  sg; int /*<<< orphan*/  data_len; int /*<<< orphan*/  data; int /*<<< orphan*/  long_data; } ;

/* Variables and functions */
 scalar_t__ MS_TPC_SET_RW_REG_ADRS ; 
 int SG_MITER_ATOMIC ; 
 int SG_MITER_FROM_SG ; 
 int SG_MITER_TO_SG ; 
 int /*<<< orphan*/  kfifo_reset (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  local_irq_save (unsigned long) ; 
 int /*<<< orphan*/  r592_flush_fifo_write (struct r592_device*) ; 
 int /*<<< orphan*/  r592_read_fifo_pio (struct r592_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  r592_write_fifo_pio (struct r592_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ sg_miter_next (struct sg_mapping_iter*) ; 
 int /*<<< orphan*/  sg_miter_start (struct sg_mapping_iter*,int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  sg_miter_stop (struct sg_mapping_iter*) ; 

__attribute__((used)) static int r592_transfer_fifo_pio(struct r592_device *dev)
{
	unsigned long flags;

	bool is_write = dev->req->tpc >= MS_TPC_SET_RW_REG_ADRS;
	struct sg_mapping_iter miter;

	kfifo_reset(&dev->pio_fifo);

	if (!dev->req->long_data) {
		if (is_write) {
			r592_write_fifo_pio(dev, dev->req->data,
							dev->req->data_len);
			r592_flush_fifo_write(dev);
		} else
			r592_read_fifo_pio(dev, dev->req->data,
							dev->req->data_len);
		return 0;
	}

	local_irq_save(flags);
	sg_miter_start(&miter, &dev->req->sg, 1, SG_MITER_ATOMIC |
		(is_write ? SG_MITER_FROM_SG : SG_MITER_TO_SG));

	/* Do the transfer fifo<->memory*/
	while (sg_miter_next(&miter))
		if (is_write)
			r592_write_fifo_pio(dev, miter.addr, miter.length);
		else
			r592_read_fifo_pio(dev, miter.addr, miter.length);


	/* Write last few non aligned bytes*/
	if (is_write)
		r592_flush_fifo_write(dev);

	sg_miter_stop(&miter);
	local_irq_restore(flags);
	return 0;
}