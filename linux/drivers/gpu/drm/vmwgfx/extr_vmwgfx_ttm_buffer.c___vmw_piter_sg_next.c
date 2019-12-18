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
struct vmw_piter {int /*<<< orphan*/  iter; } ;

/* Variables and functions */
 scalar_t__ __sg_page_iter_dma_next (int /*<<< orphan*/ *) ; 
 int __vmw_piter_non_sg_next (struct vmw_piter*) ; 

__attribute__((used)) static bool __vmw_piter_sg_next(struct vmw_piter *viter)
{
	bool ret = __vmw_piter_non_sg_next(viter);

	return __sg_page_iter_dma_next(&viter->iter) && ret;
}