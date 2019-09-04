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
typedef  scalar_t__ u32 ;
struct dpu_hw_blk_reg_map {scalar_t__ blk_off; scalar_t__ base_off; } ;

/* Variables and functions */
 int readl_relaxed (scalar_t__) ; 

int dpu_reg_read(struct dpu_hw_blk_reg_map *c, u32 reg_off)
{
	return readl_relaxed(c->base_off + c->blk_off + reg_off);
}