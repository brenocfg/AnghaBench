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
typedef  unsigned int u16 ;
struct pcidas64_private {unsigned int fifo_size_bits; unsigned int ai_fifo_segment_length; scalar_t__ main_iobase; } ;
struct pcidas64_board {struct hw_fifo_info* ai_fifo; } ;
struct hw_fifo_info {unsigned int max_segment_length; unsigned int fifo_size_reg_mask; } ;
struct comedi_device {struct pcidas64_private* private; struct pcidas64_board* board_ptr; } ;

/* Variables and functions */
 unsigned int DIV_ROUND_CLOSEST (unsigned int,int const) ; 
 scalar_t__ FIFO_SIZE_REG ; 
 int /*<<< orphan*/  writew (unsigned int,scalar_t__) ; 

__attribute__((used)) static int set_ai_fifo_segment_length(struct comedi_device *dev,
				      unsigned int num_entries)
{
	const struct pcidas64_board *board = dev->board_ptr;
	struct pcidas64_private *devpriv = dev->private;
	static const int increment_size = 0x100;
	const struct hw_fifo_info *const fifo = board->ai_fifo;
	unsigned int num_increments;
	u16 bits;

	if (num_entries < increment_size)
		num_entries = increment_size;
	if (num_entries > fifo->max_segment_length)
		num_entries = fifo->max_segment_length;

	/* 1 == 256 entries, 2 == 512 entries, etc */
	num_increments = DIV_ROUND_CLOSEST(num_entries, increment_size);

	bits = (~(num_increments - 1)) & fifo->fifo_size_reg_mask;
	devpriv->fifo_size_bits &= ~fifo->fifo_size_reg_mask;
	devpriv->fifo_size_bits |= bits;
	writew(devpriv->fifo_size_bits,
	       devpriv->main_iobase + FIFO_SIZE_REG);

	devpriv->ai_fifo_segment_length = num_increments * increment_size;

	return devpriv->ai_fifo_segment_length;
}