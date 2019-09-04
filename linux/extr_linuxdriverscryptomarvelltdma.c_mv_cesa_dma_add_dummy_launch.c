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
struct mv_cesa_tdma_desc {int dummy; } ;
struct mv_cesa_tdma_chain {int dummy; } ;
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 int PTR_ERR_OR_ZERO (struct mv_cesa_tdma_desc*) ; 
 struct mv_cesa_tdma_desc* mv_cesa_dma_add_desc (struct mv_cesa_tdma_chain*,int /*<<< orphan*/ ) ; 

int mv_cesa_dma_add_dummy_launch(struct mv_cesa_tdma_chain *chain, gfp_t flags)
{
	struct mv_cesa_tdma_desc *tdma;

	tdma = mv_cesa_dma_add_desc(chain, flags);
	return PTR_ERR_OR_ZERO(tdma);
}