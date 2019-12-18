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
typedef  int u16 ;
struct mdiobb_ctrl {int dummy; } ;

/* Variables and functions */
 int mdiobb_get_bit (struct mdiobb_ctrl*) ; 

__attribute__((used)) static u16 mdiobb_get_num(struct mdiobb_ctrl *ctrl, int bits)
{
	int i;
	u16 ret = 0;

	for (i = bits - 1; i >= 0; i--) {
		ret <<= 1;
		ret |= mdiobb_get_bit(ctrl);
	}

	return ret;
}