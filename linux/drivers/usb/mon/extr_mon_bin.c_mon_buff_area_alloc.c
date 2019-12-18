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
struct mon_reader_bin {scalar_t__ b_cnt; scalar_t__ b_size; unsigned int b_in; } ;

/* Variables and functions */
 unsigned int PKT_ALIGN ; 

__attribute__((used)) static unsigned int mon_buff_area_alloc(struct mon_reader_bin *rp,
    unsigned int size)
{
	unsigned int offset;

	size = (size + PKT_ALIGN-1) & ~(PKT_ALIGN-1);
	if (rp->b_cnt + size > rp->b_size)
		return ~0;
	offset = rp->b_in;
	rp->b_cnt += size;
	if ((rp->b_in += size) >= rp->b_size)
		rp->b_in -= rp->b_size;
	return offset;
}