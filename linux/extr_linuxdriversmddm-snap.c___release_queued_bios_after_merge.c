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
struct dm_snapshot {int /*<<< orphan*/  bios_queued_during_merge; scalar_t__ num_merging_chunks; scalar_t__ first_merging_chunk; } ;
struct bio {int dummy; } ;

/* Variables and functions */
 struct bio* bio_list_get (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct bio *__release_queued_bios_after_merge(struct dm_snapshot *s)
{
	s->first_merging_chunk = 0;
	s->num_merging_chunks = 0;

	return bio_list_get(&s->bios_queued_during_merge);
}