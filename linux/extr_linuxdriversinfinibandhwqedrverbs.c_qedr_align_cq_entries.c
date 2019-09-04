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
typedef  int u64 ;

/* Variables and functions */
 int ALIGN (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int QEDR_CQE_SIZE ; 

__attribute__((used)) static inline int qedr_align_cq_entries(int entries)
{
	u64 size, aligned_size;

	/* We allocate an extra entry that we don't report to the FW. */
	size = (entries + 1) * QEDR_CQE_SIZE;
	aligned_size = ALIGN(size, PAGE_SIZE);

	return aligned_size / QEDR_CQE_SIZE;
}