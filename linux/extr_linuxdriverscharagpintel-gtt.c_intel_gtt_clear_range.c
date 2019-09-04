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
struct TYPE_4__ {int /*<<< orphan*/  scratch_page_dma; TYPE_1__* driver; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* write_entry ) (int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 TYPE_2__ intel_private ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wmb () ; 

void intel_gtt_clear_range(unsigned int first_entry, unsigned int num_entries)
{
	unsigned int i;

	for (i = first_entry; i < (first_entry + num_entries); i++) {
		intel_private.driver->write_entry(intel_private.scratch_page_dma,
						  i, 0);
	}
	wmb();
}