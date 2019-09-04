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
typedef  int /*<<< orphan*/  u64 ;
struct ib_pd {int dummy; } ;
struct ib_mr {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  NES_DBG_MR ; 
 int /*<<< orphan*/  nes_debug (int /*<<< orphan*/ ,char*) ; 
 struct ib_mr* nes_reg_phys_mr (struct ib_pd*,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct ib_mr *nes_get_dma_mr(struct ib_pd *pd, int acc)
{
	u64 kva = 0;

	nes_debug(NES_DBG_MR, "\n");

	return nes_reg_phys_mr(pd, 0, 0xffffffffffULL, acc, &kva);
}