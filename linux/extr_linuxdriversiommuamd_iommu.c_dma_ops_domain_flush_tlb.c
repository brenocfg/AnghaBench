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
struct dma_ops_domain {int /*<<< orphan*/  domain; } ;

/* Variables and functions */
 int /*<<< orphan*/  domain_flush_complete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  domain_flush_tlb (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void dma_ops_domain_flush_tlb(struct dma_ops_domain *dom)
{
	domain_flush_tlb(&dom->domain);
	domain_flush_complete(&dom->domain);
}