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
struct skl_ddb_entry {scalar_t__ start; scalar_t__ end; } ;

/* Variables and functions */

__attribute__((used)) static inline bool skl_ddb_entries_overlap(const struct skl_ddb_entry *a,
					   const struct skl_ddb_entry *b)
{
	return a->start < b->end && b->start < a->end;
}