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
struct parsed_partitions {int dummy; } ;
typedef  int /*<<< orphan*/  sector_t ;

/* Variables and functions */

__attribute__((used)) static void parse_openbsd(struct parsed_partitions *state,
			  sector_t offset, sector_t size, int origin)
{
#ifdef CONFIG_BSD_DISKLABEL
	parse_bsd(state, offset, size, origin, "openbsd",
		  OPENBSD_MAXPARTITIONS);
#endif
}