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
struct gf100_gr {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  gf100_gr_oneinit_sm_id (struct gf100_gr*) ; 

void
gm200_gr_oneinit_sm_id(struct gf100_gr *gr)
{
	/*XXX: There's a different algorithm here I've not yet figured out. */
	gf100_gr_oneinit_sm_id(gr);
}