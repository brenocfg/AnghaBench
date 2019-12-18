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
typedef  int u32 ;
struct rockchip_rga {int* cmdbuf_virt; } ;
struct rga_ctx {struct rockchip_rga* rga; } ;

/* Variables and functions */
 unsigned int RGA_MMU_CTRL1 ; 
 unsigned int RGA_MMU_SRC1_BASE ; 
 unsigned int RGA_MODE_BASE_REG ; 
 int virt_to_phys (void*) ; 

__attribute__((used)) static void rga_cmd_set_src1_addr(struct rga_ctx *ctx, void *mmu_pages)
{
	struct rockchip_rga *rga = ctx->rga;
	u32 *dest = rga->cmdbuf_virt;
	unsigned int reg;

	reg = RGA_MMU_SRC1_BASE - RGA_MODE_BASE_REG;
	dest[reg >> 2] = virt_to_phys(mmu_pages) >> 4;

	reg = RGA_MMU_CTRL1 - RGA_MODE_BASE_REG;
	dest[reg >> 2] |= 0x7 << 4;
}