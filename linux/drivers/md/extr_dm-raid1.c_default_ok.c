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
struct mirror {int /*<<< orphan*/  error_count; int /*<<< orphan*/  ms; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_read (int /*<<< orphan*/ *) ; 
 struct mirror* get_default_mirror (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int default_ok(struct mirror *m)
{
	struct mirror *default_mirror = get_default_mirror(m->ms);

	return !atomic_read(&default_mirror->error_count);
}