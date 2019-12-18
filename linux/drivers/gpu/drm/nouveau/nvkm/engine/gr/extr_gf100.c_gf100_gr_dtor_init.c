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
struct gf100_gr_pack {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  vfree (struct gf100_gr_pack*) ; 

__attribute__((used)) static void
gf100_gr_dtor_init(struct gf100_gr_pack *pack)
{
	vfree(pack);
}