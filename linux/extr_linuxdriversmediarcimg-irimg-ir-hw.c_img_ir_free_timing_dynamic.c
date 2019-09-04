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
typedef  unsigned int u32 ;
struct img_ir_filter {int minlen; int maxlen; } ;

/* Variables and functions */
 unsigned int IMG_IR_MAXLEN ; 
 unsigned int IMG_IR_MAXLEN_SHIFT ; 
 unsigned int IMG_IR_MINLEN ; 
 unsigned int IMG_IR_MINLEN_SHIFT ; 

__attribute__((used)) static u32 img_ir_free_timing_dynamic(u32 st_ft, struct img_ir_filter *filter)
{
	unsigned int minlen, maxlen, newminlen, newmaxlen;

	/* round minlen, maxlen to multiple of 2 */
	newminlen = filter->minlen & -2;
	newmaxlen = (filter->maxlen + 1) & -2;
	/* extract min/max len from register */
	minlen = (st_ft & IMG_IR_MINLEN) >> IMG_IR_MINLEN_SHIFT;
	maxlen = (st_ft & IMG_IR_MAXLEN) >> IMG_IR_MAXLEN_SHIFT;
	/* if the new values are more restrictive, update the register value */
	if (newminlen > minlen) {
		st_ft &= ~IMG_IR_MINLEN;
		st_ft |= newminlen << IMG_IR_MINLEN_SHIFT;
	}
	if (newmaxlen < maxlen) {
		st_ft &= ~IMG_IR_MAXLEN;
		st_ft |= newmaxlen << IMG_IR_MAXLEN_SHIFT;
	}
	return st_ft;
}