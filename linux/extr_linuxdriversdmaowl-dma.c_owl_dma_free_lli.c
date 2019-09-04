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
struct owl_dma_lli {int /*<<< orphan*/  phys; int /*<<< orphan*/  node; } ;
struct owl_dma {int /*<<< orphan*/  lli_pool; } ;

/* Variables and functions */
 int /*<<< orphan*/  dma_pool_free (int /*<<< orphan*/ ,struct owl_dma_lli*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void owl_dma_free_lli(struct owl_dma *od,
			     struct owl_dma_lli *lli)
{
	list_del(&lli->node);
	dma_pool_free(od->lli_pool, lli, lli->phys);
}