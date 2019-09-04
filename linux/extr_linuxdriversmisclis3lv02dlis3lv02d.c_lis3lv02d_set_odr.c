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
typedef  int u8 ;
struct lis3lv02d {int odr_mask; int* odrs; int /*<<< orphan*/  (* write ) (struct lis3lv02d*,int /*<<< orphan*/ ,int) ;int /*<<< orphan*/  (* read ) (struct lis3lv02d*,int /*<<< orphan*/ ,int*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  CTRL_REG1 ; 
 int EINVAL ; 
 int ffs (int) ; 
 int hweight_long (int) ; 
 int /*<<< orphan*/  stub1 (struct lis3lv02d*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  stub2 (struct lis3lv02d*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int lis3lv02d_set_odr(struct lis3lv02d *lis3, int rate)
{
	u8 ctrl;
	int i, len, shift;

	if (!rate)
		return -EINVAL;

	lis3->read(lis3, CTRL_REG1, &ctrl);
	ctrl &= ~lis3->odr_mask;
	len = 1 << hweight_long(lis3->odr_mask); /* # of possible values */
	shift = ffs(lis3->odr_mask) - 1;

	for (i = 0; i < len; i++)
		if (lis3->odrs[i] == rate) {
			lis3->write(lis3, CTRL_REG1,
					ctrl | (i << shift));
			return 0;
		}
	return -EINVAL;
}