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
struct mv_cesa_req {int dummy; } ;

/* Variables and functions */
 int CESA_SA_INT_ACC0_IDMA_DONE ; 
 int CESA_SA_INT_IDMA_OWN_ERR ; 
 int EINPROGRESS ; 
 int EINVAL ; 

__attribute__((used)) static inline int mv_cesa_dma_process(struct mv_cesa_req *dreq,
				      u32 status)
{
	if (!(status & CESA_SA_INT_ACC0_IDMA_DONE))
		return -EINPROGRESS;

	if (status & CESA_SA_INT_IDMA_OWN_ERR)
		return -EINVAL;

	return 0;
}