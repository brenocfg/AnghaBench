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
typedef  size_t u64 ;
struct rxe_mem {int type; size_t iova; size_t length; } ;

/* Variables and functions */
 int EFAULT ; 
#define  RXE_MEM_TYPE_DMA 130 
#define  RXE_MEM_TYPE_FMR 129 
#define  RXE_MEM_TYPE_MR 128 

int mem_check_range(struct rxe_mem *mem, u64 iova, size_t length)
{
	switch (mem->type) {
	case RXE_MEM_TYPE_DMA:
		return 0;

	case RXE_MEM_TYPE_MR:
	case RXE_MEM_TYPE_FMR:
		if (iova < mem->iova ||
		    length > mem->length ||
		    iova > mem->iova + mem->length - length)
			return -EFAULT;
		return 0;

	default:
		return -EFAULT;
	}
}