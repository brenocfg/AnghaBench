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
struct gf100_gr {scalar_t__ firmware; } ;

/* Variables and functions */
 int gf100_gr_init_ctxctl_ext (struct gf100_gr*) ; 
 int gf100_gr_init_ctxctl_int (struct gf100_gr*) ; 

int
gf100_gr_init_ctxctl(struct gf100_gr *gr)
{
	int ret;

	if (gr->firmware)
		ret = gf100_gr_init_ctxctl_ext(gr);
	else
		ret = gf100_gr_init_ctxctl_int(gr);

	return ret;
}