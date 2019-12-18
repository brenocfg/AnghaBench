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
typedef  int /*<<< orphan*/  dma_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  sg_page_iter_dma_address (int /*<<< orphan*/ *) ; 

__attribute__((used)) static dma_addr_t __vmw_piter_sg_addr(struct vmw_piter *viter)
{
	return sg_page_iter_dma_address(&viter->iter);
}