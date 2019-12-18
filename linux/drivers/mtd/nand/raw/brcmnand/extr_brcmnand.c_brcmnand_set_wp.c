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
struct brcmnand_controller {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BRCMNAND_CS_SELECT ; 
 int /*<<< orphan*/  CS_SELECT_NAND_WP ; 
 int /*<<< orphan*/  brcmnand_rmw_reg (struct brcmnand_controller*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void brcmnand_set_wp(struct brcmnand_controller *ctrl, bool en)
{
	u32 val = en ? CS_SELECT_NAND_WP : 0;

	brcmnand_rmw_reg(ctrl, BRCMNAND_CS_SELECT, CS_SELECT_NAND_WP, 0, val);
}