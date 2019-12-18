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
struct mirror_set {int /*<<< orphan*/  default_mirror; struct mirror* mirror; } ;
struct mirror {struct mirror_set* ms; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void set_default_mirror(struct mirror *m)
{
	struct mirror_set *ms = m->ms;
	struct mirror *m0 = &(ms->mirror[0]);

	atomic_set(&ms->default_mirror, m - m0);
}