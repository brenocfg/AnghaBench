#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u64 ;
struct parsed_partitions {int limit; TYPE_2__* parts; } ;
struct TYPE_3__ {int /*<<< orphan*/  volname; } ;
struct TYPE_4__ {scalar_t__ size; scalar_t__ from; TYPE_1__ info; scalar_t__ has_info; } ;

/* Variables and functions */
 scalar_t__ has_overlaps (scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  overlaps_warns_header () ; 
 int /*<<< orphan*/  pr_warn (char*,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static void cmdline_parts_verifier(int slot, struct parsed_partitions *state)
{
	int i;
	bool header = true;

	for (; slot < state->limit && state->parts[slot].has_info; slot++) {
		for (i = slot+1; i < state->limit && state->parts[i].has_info;
		     i++) {
			if (has_overlaps(state->parts[slot].from,
					 state->parts[slot].size,
					 state->parts[i].from,
					 state->parts[i].size)) {
				if (header) {
					header = false;
					overlaps_warns_header();
				}
				pr_warn("%s[%llu,%llu] overlaps with "
					"%s[%llu,%llu].",
					state->parts[slot].info.volname,
					(u64)state->parts[slot].from << 9,
					(u64)state->parts[slot].size << 9,
					state->parts[i].info.volname,
					(u64)state->parts[i].from << 9,
					(u64)state->parts[i].size << 9);
			}
		}
	}
}