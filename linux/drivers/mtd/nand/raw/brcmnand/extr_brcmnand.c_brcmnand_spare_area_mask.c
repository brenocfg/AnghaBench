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
struct brcmnand_controller {int nand_version; } ;

/* Variables and functions */
 int /*<<< orphan*/  GENMASK (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline u32 brcmnand_spare_area_mask(struct brcmnand_controller *ctrl)
{
	if (ctrl->nand_version == 0x0702)
		return GENMASK(7, 0);
	else if (ctrl->nand_version >= 0x0600)
		return GENMASK(6, 0);
	else
		return GENMASK(5, 0);
}