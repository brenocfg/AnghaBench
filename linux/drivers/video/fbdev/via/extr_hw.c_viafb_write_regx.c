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
struct io_reg {int /*<<< orphan*/  mask; int /*<<< orphan*/  value; int /*<<< orphan*/  index; int /*<<< orphan*/  port; } ;

/* Variables and functions */
 int /*<<< orphan*/  via_write_reg_mask (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void viafb_write_regx(struct io_reg RegTable[], int ItemNum)
{
	int i;

	/*DEBUG_MSG(KERN_INFO "Table Size : %x!!\n",ItemNum ); */

	for (i = 0; i < ItemNum; i++)
		via_write_reg_mask(RegTable[i].port, RegTable[i].index,
			RegTable[i].value, RegTable[i].mask);
}