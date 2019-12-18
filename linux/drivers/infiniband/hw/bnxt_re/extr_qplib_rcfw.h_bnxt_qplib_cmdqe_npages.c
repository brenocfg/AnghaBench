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
 int BNXT_QPLIB_CMDQE_BYTES (int) ; 
 int PAGE_SIZE ; 

__attribute__((used)) static inline u32 bnxt_qplib_cmdqe_npages(u32 depth)
{
	u32 npages;

	npages = BNXT_QPLIB_CMDQE_BYTES(depth) / PAGE_SIZE;
	if (BNXT_QPLIB_CMDQE_BYTES(depth) % PAGE_SIZE)
		npages++;
	return npages;
}