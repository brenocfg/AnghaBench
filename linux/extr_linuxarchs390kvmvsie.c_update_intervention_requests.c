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
struct TYPE_4__ {int /*<<< orphan*/  cpuflags; } ;
struct vsie_page {TYPE_2__ scb_s; TYPE_1__* scb_o; } ;
struct TYPE_3__ {int /*<<< orphan*/  cpuflags; } ;

/* Variables and functions */
 int CPUSTAT_EXT_INT ; 
 int CPUSTAT_IO_INT ; 
 int CPUSTAT_STOP_INT ; 
 int /*<<< orphan*/  atomic_andnot (int const,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_or (int,int /*<<< orphan*/ *) ; 
 int atomic_read (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void update_intervention_requests(struct vsie_page *vsie_page)
{
	const int bits = CPUSTAT_STOP_INT | CPUSTAT_IO_INT | CPUSTAT_EXT_INT;
	int cpuflags;

	cpuflags = atomic_read(&vsie_page->scb_o->cpuflags);
	atomic_andnot(bits, &vsie_page->scb_s.cpuflags);
	atomic_or(cpuflags & bits, &vsie_page->scb_s.cpuflags);
}