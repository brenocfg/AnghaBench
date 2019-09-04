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
typedef  int /*<<< orphan*/  dma_addr_t ;
struct TYPE_4__ {TYPE_1__* driver; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* chipset_flush ) () ;int /*<<< orphan*/  (* write_entry ) (int /*<<< orphan*/ ,unsigned int,unsigned int) ;} ;

/* Variables and functions */
 TYPE_2__ intel_private ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  stub2 () ; 

void intel_gtt_insert_page(dma_addr_t addr,
			   unsigned int pg,
			   unsigned int flags)
{
	intel_private.driver->write_entry(addr, pg, flags);
	if (intel_private.driver->chipset_flush)
		intel_private.driver->chipset_flush();
}