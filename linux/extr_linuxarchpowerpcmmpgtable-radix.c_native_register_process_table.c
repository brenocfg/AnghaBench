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
struct TYPE_2__ {int /*<<< orphan*/  patb0; } ;

/* Variables and functions */
 unsigned long PATB_GR ; 
 unsigned long be64_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmu_partition_table_set_entry (int /*<<< orphan*/ ,unsigned long,unsigned long) ; 
 TYPE_1__* partition_tb ; 

__attribute__((used)) static int native_register_process_table(unsigned long base, unsigned long pg_sz,
					 unsigned long table_size)
{
	unsigned long patb0, patb1;

	patb0 = be64_to_cpu(partition_tb[0].patb0);
	patb1 = base | table_size | PATB_GR;

	mmu_partition_table_set_entry(0, patb0, patb1);

	return 0;
}