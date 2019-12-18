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
struct comedi_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ni_set_bitfield (struct comedi_device*,int,unsigned int,unsigned int) ; 

__attribute__((used)) static inline void ni_set_bits(struct comedi_device *dev, int reg,
			       unsigned int bits, unsigned int value)
{
	unsigned int bit_values;

	if (value)
		bit_values = bits;
	else
		bit_values = 0;
	ni_set_bitfield(dev, reg, bits, bit_values);
}