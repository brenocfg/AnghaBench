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
typedef  int /*<<< orphan*/  u32 ;
struct brcmnand_controller {scalar_t__ nand_fc; } ;

/* Variables and functions */
 int /*<<< orphan*/  __raw_readl (scalar_t__) ; 

__attribute__((used)) static inline u32 brcmnand_read_fc(struct brcmnand_controller *ctrl, int word)
{
	return __raw_readl(ctrl->nand_fc + word * 4);
}