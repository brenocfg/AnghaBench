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

/* Variables and functions */

__attribute__((used)) static int setsize(unsigned long capacity, unsigned int *cyls, unsigned int *hds,
		   unsigned int *secs)
{
	unsigned int rv = 0;
	unsigned long heads, sectors, cylinders, temp;

	cylinders = 1024L;	/* Set number of cylinders to max */
	sectors = 62L;		/* Maximize sectors per track */

	temp = cylinders * sectors;	/* Compute divisor for heads */
	heads = capacity / temp;	/* Compute value for number of heads */
	if (capacity % temp) {	/* If no remainder, done! */
		heads++;	/* Else, increment number of heads */
		temp = cylinders * heads;	/* Compute divisor for sectors */
		sectors = capacity / temp;	/* Compute value for sectors per
						   track */
		if (capacity % temp) {	/* If no remainder, done! */
			sectors++;	/* Else, increment number of sectors */
			temp = heads * sectors;		/* Compute divisor for cylinders */
			cylinders = capacity / temp;	/* Compute number of cylinders */
		}
	}
	if (cylinders == 0)
		rv = (unsigned) -1;	/* Give error if 0 cylinders */

	*cyls = (unsigned int) cylinders;	/* Stuff return values */
	*secs = (unsigned int) sectors;
	*hds = (unsigned int) heads;
	return (rv);
}