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
struct pstore {TYPE_1__* store; int /*<<< orphan*/  area; } ;
struct TYPE_2__ {int chunk_size; } ;

/* Variables and functions */
 int SECTOR_SHIFT ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void zero_memory_area(struct pstore *ps)
{
	memset(ps->area, 0, ps->store->chunk_size << SECTOR_SHIFT);
}