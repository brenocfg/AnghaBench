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
struct TYPE_2__ {int prog0c; int /*<<< orphan*/  cpuflags; } ;
struct vsie_page {TYPE_1__ scb_s; } ;

/* Variables and functions */
 int /*<<< orphan*/  CPUSTAT_STOP_INT ; 
 int PROG_IN_SIE ; 
 int /*<<< orphan*/  atomic_or (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cpu_relax () ; 
 int /*<<< orphan*/  prefix_unmapped (struct vsie_page*) ; 

__attribute__((used)) static void prefix_unmapped_sync(struct vsie_page *vsie_page)
{
	prefix_unmapped(vsie_page);
	if (vsie_page->scb_s.prog0c & PROG_IN_SIE)
		atomic_or(CPUSTAT_STOP_INT, &vsie_page->scb_s.cpuflags);
	while (vsie_page->scb_s.prog0c & PROG_IN_SIE)
		cpu_relax();
}