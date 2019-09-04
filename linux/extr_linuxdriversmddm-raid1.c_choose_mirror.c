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
struct mirror_set {int /*<<< orphan*/  nr_mirrors; int /*<<< orphan*/  mirror; } ;
struct mirror {int /*<<< orphan*/  error_count; } ;
typedef  int /*<<< orphan*/  sector_t ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_read (int /*<<< orphan*/ *) ; 
 struct mirror* get_default_mirror (struct mirror_set*) ; 
 scalar_t__ likely (int) ; 

__attribute__((used)) static struct mirror *choose_mirror(struct mirror_set *ms, sector_t sector)
{
	struct mirror *m = get_default_mirror(ms);

	do {
		if (likely(!atomic_read(&m->error_count)))
			return m;

		if (m-- == ms->mirror)
			m += ms->nr_mirrors;
	} while (m != get_default_mirror(ms));

	return NULL;
}