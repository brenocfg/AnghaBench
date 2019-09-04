#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct mirror_set {unsigned int nr_mirrors; TYPE_1__* mirror; scalar_t__ leg_failure; } ;
struct TYPE_2__ {scalar_t__ error_type; int /*<<< orphan*/  error_count; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void reset_ms_flags(struct mirror_set *ms)
{
	unsigned int m;

	ms->leg_failure = 0;
	for (m = 0; m < ms->nr_mirrors; m++) {
		atomic_set(&(ms->mirror[m].error_count), 0);
		ms->mirror[m].error_type = 0;
	}
}