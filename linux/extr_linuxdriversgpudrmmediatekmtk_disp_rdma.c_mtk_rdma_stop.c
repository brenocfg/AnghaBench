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
struct mtk_ddp_comp {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DISP_REG_RDMA_GLOBAL_CON ; 
 int /*<<< orphan*/  RDMA_ENGINE_EN ; 
 int /*<<< orphan*/  rdma_update_bits (struct mtk_ddp_comp*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mtk_rdma_stop(struct mtk_ddp_comp *comp)
{
	rdma_update_bits(comp, DISP_REG_RDMA_GLOBAL_CON, RDMA_ENGINE_EN, 0);
}