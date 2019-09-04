#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u64 ;
struct TYPE_2__ {int (* read_pic ) (int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* write_pic ) (int /*<<< orphan*/ ,int) ;} ;

/* Variables and functions */
 int PIC_UPPER_INDEX ; 
 TYPE_1__* pcr_ops ; 
 int stub1 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void sparc_default_write_pmc(int idx, u64 val)
{
	u64 shift, mask, pic;

	shift = 0;
	if (idx == PIC_UPPER_INDEX)
		shift = 32;

	mask = ((u64) 0xffffffff) << shift;
	val <<= shift;

	pic = pcr_ops->read_pic(0);
	pic &= ~mask;
	pic |= val;
	pcr_ops->write_pic(0, pic);
}