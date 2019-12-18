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
typedef  unsigned int u32 ;
struct brcmnand_controller {int dummy; } ;
typedef  enum brcmnand_reg { ____Placeholder_brcmnand_reg } brcmnand_reg ;

/* Variables and functions */
 unsigned int brcmnand_read_reg (struct brcmnand_controller*,int) ; 
 int /*<<< orphan*/  brcmnand_write_reg (struct brcmnand_controller*,int,unsigned int) ; 

__attribute__((used)) static inline void brcmnand_rmw_reg(struct brcmnand_controller *ctrl,
				    enum brcmnand_reg reg, u32 mask, unsigned
				    int shift, u32 val)
{
	u32 tmp = brcmnand_read_reg(ctrl, reg);

	tmp &= ~mask;
	tmp |= val << shift;
	brcmnand_write_reg(ctrl, reg, tmp);
}