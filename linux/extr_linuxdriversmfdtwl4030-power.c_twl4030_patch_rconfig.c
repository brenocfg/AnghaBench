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
struct twl4030_resconfig {scalar_t__ resource; } ;

/* Variables and functions */

__attribute__((used)) static void twl4030_patch_rconfig(struct twl4030_resconfig *common,
				  struct twl4030_resconfig *board)
{
	while (common->resource) {
		struct twl4030_resconfig *b = board;

		while (b->resource) {
			if (b->resource == common->resource) {
				*common = *b;
				break;
			}
			b++;
		}
		common++;
	}
}