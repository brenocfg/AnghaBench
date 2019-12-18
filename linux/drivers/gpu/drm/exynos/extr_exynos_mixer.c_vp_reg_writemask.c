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
struct mixer_context {int vp_regs; } ;

/* Variables and functions */
 int vp_reg_read (struct mixer_context*,int) ; 
 int /*<<< orphan*/  writel (int,int) ; 

__attribute__((used)) static inline void vp_reg_writemask(struct mixer_context *ctx, u32 reg_id,
				 u32 val, u32 mask)
{
	u32 old = vp_reg_read(ctx, reg_id);

	val = (val & mask) | (old & ~mask);
	writel(val, ctx->vp_regs + reg_id);
}