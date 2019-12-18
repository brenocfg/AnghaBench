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
struct comedi_device {scalar_t__ iobase; } ;

/* Variables and functions */
 scalar_t__ AIO_IIRO_16_INPUT_0_7 ; 
 scalar_t__ AIO_IIRO_16_INPUT_8_15 ; 
 int inb (scalar_t__) ; 

__attribute__((used)) static unsigned int aio_iiro_16_read_inputs(struct comedi_device *dev)
{
	unsigned int val;

	val = inb(dev->iobase + AIO_IIRO_16_INPUT_0_7);
	val |= inb(dev->iobase + AIO_IIRO_16_INPUT_8_15) << 8;

	return val;
}