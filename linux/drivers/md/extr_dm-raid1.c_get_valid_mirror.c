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
struct mirror_set {int nr_mirrors; struct mirror* mirror; } ;
struct mirror {int /*<<< orphan*/  error_count; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_read (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct mirror *get_valid_mirror(struct mirror_set *ms)
{
	struct mirror *m;

	for (m = ms->mirror; m < ms->mirror + ms->nr_mirrors; m++)
		if (!atomic_read(&m->error_count))
			return m;

	return NULL;
}