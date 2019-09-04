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
typedef  int /*<<< orphan*/  u64 ;

/* Variables and functions */
 int CMDQ_WQE_SIZE ; 
 int FIRST_DATA_TO_WRITE_LAST ; 
 int /*<<< orphan*/  memcpy (void*,void*,int) ; 
 int /*<<< orphan*/  wmb () ; 

__attribute__((used)) static void cmdq_wqe_fill(void *dst, void *src)
{
	memcpy(dst + FIRST_DATA_TO_WRITE_LAST, src + FIRST_DATA_TO_WRITE_LAST,
	       CMDQ_WQE_SIZE - FIRST_DATA_TO_WRITE_LAST);

	wmb();          /* The first 8 bytes should be written last */

	*(u64 *)dst = *(u64 *)src;
}