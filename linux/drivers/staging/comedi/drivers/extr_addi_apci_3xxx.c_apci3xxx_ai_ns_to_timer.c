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
struct comedi_device {struct apci3xxx_private* private; struct apci3xxx_boardinfo* board_ptr; } ;
struct apci3xxx_private {int ai_time_base; unsigned int ai_timer; } ;
struct apci3xxx_boardinfo {int ai_conv_units; } ;

/* Variables and functions */
#define  CMDF_ROUND_DOWN 130 
 unsigned int CMDF_ROUND_MASK ; 
#define  CMDF_ROUND_NEAREST 129 
#define  CMDF_ROUND_UP 128 
 unsigned int DIV_ROUND_CLOSEST (unsigned int,unsigned int) ; 
 unsigned int DIV_ROUND_UP (unsigned int,unsigned int) ; 
 int EINVAL ; 

__attribute__((used)) static int apci3xxx_ai_ns_to_timer(struct comedi_device *dev,
				   unsigned int *ns, unsigned int flags)
{
	const struct apci3xxx_boardinfo *board = dev->board_ptr;
	struct apci3xxx_private *devpriv = dev->private;
	unsigned int base;
	unsigned int timer;
	int time_base;

	/* time_base: 0 = ns, 1 = us, 2 = ms */
	for (time_base = 0; time_base < 3; time_base++) {
		/* skip unsupported time bases */
		if (!(board->ai_conv_units & (1 << time_base)))
			continue;

		switch (time_base) {
		case 0:
			base = 1;
			break;
		case 1:
			base = 1000;
			break;
		case 2:
			base = 1000000;
			break;
		}

		switch (flags & CMDF_ROUND_MASK) {
		case CMDF_ROUND_NEAREST:
		default:
			timer = DIV_ROUND_CLOSEST(*ns, base);
			break;
		case CMDF_ROUND_DOWN:
			timer = *ns / base;
			break;
		case CMDF_ROUND_UP:
			timer = DIV_ROUND_UP(*ns, base);
			break;
		}

		if (timer < 0x10000) {
			devpriv->ai_time_base = time_base;
			devpriv->ai_timer = timer;
			*ns = timer * time_base;
			return 0;
		}
	}
	return -EINVAL;
}