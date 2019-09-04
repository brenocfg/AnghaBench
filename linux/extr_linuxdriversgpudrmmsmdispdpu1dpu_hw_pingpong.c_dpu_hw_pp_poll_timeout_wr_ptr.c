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
struct dpu_hw_blk_reg_map {scalar_t__ blk_off; scalar_t__ base_off; } ;
struct dpu_hw_pingpong {struct dpu_hw_blk_reg_map hw; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ PP_LINE_COUNT ; 
 int readl_poll_timeout (scalar_t__,int,int,int,int) ; 

__attribute__((used)) static int dpu_hw_pp_poll_timeout_wr_ptr(struct dpu_hw_pingpong *pp,
		u32 timeout_us)
{
	struct dpu_hw_blk_reg_map *c;
	u32 val;
	int rc;

	if (!pp)
		return -EINVAL;

	c = &pp->hw;
	rc = readl_poll_timeout(c->base_off + c->blk_off + PP_LINE_COUNT,
			val, (val & 0xffff) >= 1, 10, timeout_us);

	return rc;
}