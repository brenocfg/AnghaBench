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
struct protection_domain {int flags; } ;

/* Variables and functions */
 int PD_DMA_OPS_MASK ; 

__attribute__((used)) static bool dma_ops_domain(struct protection_domain *domain)
{
	return domain->flags & PD_DMA_OPS_MASK;
}