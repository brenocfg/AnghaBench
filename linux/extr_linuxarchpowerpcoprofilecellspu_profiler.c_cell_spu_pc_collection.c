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
typedef  int u32 ;

/* Variables and functions */
 int CBE_PM_TRACE_BUF_EMPTY ; 
 int TRACE_ARRAY_SIZE ; 
 int cbe_read_pm (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spu_pc_extract (int,int) ; 
 int /*<<< orphan*/  trace_address ; 

__attribute__((used)) static int cell_spu_pc_collection(int cpu)
{
	u32 trace_addr;
	int entry;

	/* process the collected SPU PC for the node */

	entry = 0;

	trace_addr = cbe_read_pm(cpu, trace_address);
	while (!(trace_addr & CBE_PM_TRACE_BUF_EMPTY)) {
		/* there is data in the trace buffer to process */
		spu_pc_extract(cpu, entry);

		entry++;

		if (entry >= TRACE_ARRAY_SIZE)
			/* spu_samples is full */
			break;

		trace_addr = cbe_read_pm(cpu, trace_address);
	}

	return entry;
}