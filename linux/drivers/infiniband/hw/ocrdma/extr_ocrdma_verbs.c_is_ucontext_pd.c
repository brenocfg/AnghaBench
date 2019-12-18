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
struct ocrdma_ucontext {struct ocrdma_pd* cntxt_pd; } ;
struct ocrdma_pd {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static inline int is_ucontext_pd(struct ocrdma_ucontext *uctx,
				 struct ocrdma_pd *pd)
{
	return (uctx->cntxt_pd == pd);
}