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
typedef  int u32 ;

/* Variables and functions */

u8 i40iw_get_encoded_wqe_size(u32 wqsize, bool cqpsq)
{
	u8 encoded_size = 0;

	/* cqp sq's hw coded value starts from 1 for size of 4
	 * while it starts from 0 for qp' wq's.
	 */
	if (cqpsq)
		encoded_size = 1;
	wqsize >>= 2;
	while (wqsize >>= 1)
		encoded_size++;
	return encoded_size;
}