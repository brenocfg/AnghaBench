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
struct brcmnand_controller {scalar_t__ nand_base; } ;

/* Variables and functions */
 int /*<<< orphan*/  brcmnand_writel (scalar_t__,scalar_t__) ; 

__attribute__((used)) static inline void nand_writereg(struct brcmnand_controller *ctrl, u32 offs,
				 u32 val)
{
	brcmnand_writel(val, ctrl->nand_base + offs);
}