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
struct vmw_piter {int /*<<< orphan*/  (* dma_address ) (struct vmw_piter*) ;} ;
typedef  int /*<<< orphan*/  dma_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (struct vmw_piter*) ; 

__attribute__((used)) static inline dma_addr_t vmw_piter_dma_addr(struct vmw_piter *viter)
{
	return viter->dma_address(viter);
}