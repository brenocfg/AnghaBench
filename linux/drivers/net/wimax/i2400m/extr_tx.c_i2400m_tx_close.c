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
struct i2400m_msg_hdr {int size; int offset; int /*<<< orphan*/  padding; int /*<<< orphan*/  num_pls; } ;
struct i2400m {struct i2400m_msg_hdr* tx_msg; int /*<<< orphan*/  tx_out; int /*<<< orphan*/  tx_in; int /*<<< orphan*/  tx_buf; int /*<<< orphan*/  bus_tx_block_size; } ;
struct device {int dummy; } ;

/* Variables and functions */
 size_t ALIGN (size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  I2400M_PL_ALIGN ; 
 int I2400M_TX_PLD_SIZE ; 
 int I2400M_TX_SKIP ; 
 void* TAIL_FULL ; 
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  cpu_to_le16 (size_t) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,unsigned long,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct device* i2400m_dev (struct i2400m*) ; 
 void* i2400m_tx_fifo_push (struct i2400m*,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 unsigned int le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memmove (struct i2400m_msg_hdr*,struct i2400m_msg_hdr*,size_t) ; 
 int /*<<< orphan*/  memset (void*,int,size_t) ; 
 int /*<<< orphan*/  pld ; 
 size_t struct_size (struct i2400m_msg_hdr*,int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static
void i2400m_tx_close(struct i2400m *i2400m)
{
	struct device *dev = i2400m_dev(i2400m);
	struct i2400m_msg_hdr *tx_msg = i2400m->tx_msg;
	struct i2400m_msg_hdr *tx_msg_moved;
	size_t aligned_size, padding, hdr_size;
	void *pad_buf;
	unsigned num_pls;

	if (tx_msg->size & I2400M_TX_SKIP)	/* a skipper? nothing to do */
		goto out;
	num_pls = le16_to_cpu(tx_msg->num_pls);
	/* We can get this situation when a new message was started
	 * and there was no space to add payloads before hitting the
	 tail (and taking padding into consideration). */
	if (num_pls == 0) {
		tx_msg->size |= I2400M_TX_SKIP;
		goto out;
	}
	/* Relocate the message header
	 *
	 * Find the current header size, align it to 16 and if we need
	 * to move it so the tail is next to the payloads, move it and
	 * set the offset.
	 *
	 * If it moved, this header is good only for transmission; the
	 * original one (it is kept if we moved) is still used to
	 * figure out where the next TX message starts (and where the
	 * offset to the moved header is).
	 */
	hdr_size = struct_size(tx_msg, pld, le16_to_cpu(tx_msg->num_pls));
	hdr_size = ALIGN(hdr_size, I2400M_PL_ALIGN);
	tx_msg->offset = I2400M_TX_PLD_SIZE - hdr_size;
	tx_msg_moved = (void *) tx_msg + tx_msg->offset;
	memmove(tx_msg_moved, tx_msg, hdr_size);
	tx_msg_moved->size -= tx_msg->offset;
	/*
	 * Now figure out how much we have to add to the (moved!)
	 * message so the size is a multiple of i2400m->bus_tx_block_size.
	 */
	aligned_size = ALIGN(tx_msg_moved->size, i2400m->bus_tx_block_size);
	padding = aligned_size - tx_msg_moved->size;
	if (padding > 0) {
		pad_buf = i2400m_tx_fifo_push(i2400m, padding, 0, 0);
		if (WARN_ON(pad_buf == NULL || pad_buf == TAIL_FULL)) {
			/* This should not happen -- append should verify
			 * there is always space left at least to append
			 * tx_block_size */
			dev_err(dev,
				"SW BUG! Possible data leakage from memory the "
				"device should not read for padding - "
				"size %lu aligned_size %zu tx_buf %p in "
				"%zu out %zu\n",
				(unsigned long) tx_msg_moved->size,
				aligned_size, i2400m->tx_buf, i2400m->tx_in,
				i2400m->tx_out);
		} else
			memset(pad_buf, 0xad, padding);
	}
	tx_msg_moved->padding = cpu_to_le16(padding);
	tx_msg_moved->size += padding;
	if (tx_msg != tx_msg_moved)
		tx_msg->size += padding;
out:
	i2400m->tx_msg = NULL;
}