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
#define  CMDF_ROUND_DOWN 130 
 unsigned int CMDF_ROUND_MASK ; 
#define  CMDF_ROUND_NEAREST 129 
#define  CMDF_ROUND_UP 128 
 unsigned int DIV_ROUND_CLOSEST (unsigned int,unsigned int) ; 
 unsigned int DIV_ROUND_UP (unsigned int,unsigned int) ; 

__attribute__((used)) static int dt3k_ns_to_timer(unsigned int timer_base, unsigned int *nanosec,
			    unsigned int flags)
{
	unsigned int divider, base, prescale;

	/* This function needs improvement */
	/* Don't know if divider==0 works. */

	for (prescale = 0; prescale < 16; prescale++) {
		base = timer_base * (prescale + 1);
		switch (flags & CMDF_ROUND_MASK) {
		case CMDF_ROUND_NEAREST:
		default:
			divider = DIV_ROUND_CLOSEST(*nanosec, base);
			break;
		case CMDF_ROUND_DOWN:
			divider = (*nanosec) / base;
			break;
		case CMDF_ROUND_UP:
			divider = DIV_ROUND_UP(*nanosec, base);
			break;
		}
		if (divider < 65536) {
			*nanosec = divider * base;
			return (prescale << 16) | (divider);
		}
	}

	prescale = 15;
	base = timer_base * (prescale + 1);
	divider = 65535;
	*nanosec = divider * base;
	return (prescale << 16) | (divider);
}