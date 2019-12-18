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
struct comedi_subdevice {int dummy; } ;

/* Variables and functions */
 unsigned int AREF_COMMON ; 
 unsigned int AREF_DIFF ; 
 unsigned char CMEN ; 
 unsigned int CR_AREF (unsigned int) ; 
 unsigned int CR_RANGE (unsigned int) ; 
 unsigned char SD ; 
 unsigned char UB ; 
 unsigned char UQEN ; 
 scalar_t__ comedi_range_is_unipolar (struct comedi_subdevice*,unsigned int) ; 

__attribute__((used)) static unsigned char das1800_ai_chanspec_bits(struct comedi_subdevice *s,
					      unsigned int chanspec)
{
	unsigned int range = CR_RANGE(chanspec);
	unsigned int aref = CR_AREF(chanspec);
	unsigned char bits;

	bits = UQEN;
	if (aref != AREF_DIFF)
		bits |= SD;
	if (aref == AREF_COMMON)
		bits |= CMEN;
	if (comedi_range_is_unipolar(s, range))
		bits |= UB;

	return bits;
}