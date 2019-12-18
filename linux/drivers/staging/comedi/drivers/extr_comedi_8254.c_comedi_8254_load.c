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
struct comedi_8254 {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 unsigned int I8254_BCD ; 
 unsigned int I8254_MODE5 ; 
 int /*<<< orphan*/  comedi_8254_set_mode (struct comedi_8254*,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  comedi_8254_write (struct comedi_8254*,unsigned int,unsigned int) ; 

int comedi_8254_load(struct comedi_8254 *i8254, unsigned int counter,
		     unsigned int val, unsigned int mode)
{
	if (counter > 2)
		return -EINVAL;
	if (val > 0xffff)
		return -EINVAL;
	if (mode > (I8254_MODE5 | I8254_BCD))
		return -EINVAL;

	comedi_8254_set_mode(i8254, counter, mode);
	comedi_8254_write(i8254, counter, val);

	return 0;
}